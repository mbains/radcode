#include <QtGui>
#include "borderlayout.h" //auto added includes after this line


#include <QtCore/qnamespace.h>

#include <qlayout.h>
#include <qlayoutitem.h>



BorderLayout::BorderLayout(QWidget *parent, int margin, int spacing)
: QLayout(parent)
{
    setMargin(margin);
    //set the spacing between widgets inside the layout
    setSpacing(spacing);
}

BorderLayout::BorderLayout(int spacing)
{
    setSpacing(spacing);
}

BorderLayout::~BorderLayout()
{
    QLayoutItem *l;
    while((l = takeAt(0)))
        delete l;

}

void BorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

void BorderLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

Qt::Orientations BorderLayout::expandingDirections() const
{
    return Qt::Horizontal | Qt::Vertical;
}

bool BorderLayout::hasHeightForWidth() const
{
    return false;
}


int BorderLayout::count() const
{
    return list.size();
}

QLayoutItem *BorderLayout::itemAt(int index) const
{
    ItemWrapper *wrapper = list.value(index);
    if(wrapper)
        return wrapper->item;
    else
        return 0;
}

QSize BorderLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

void BorderLayout::setGeometry(const QRect& rect)
{
    ItemWrapper *center = 0;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;
    int i;

    //call base class
    QLayout::setGeometry(rect);

    for (i = 0; i < list.size(); ++i)
    {
        //for every item in list
        //list contains QLayoutItem wrappers
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;
        
        if (position == North)
        {
            // on north, change only the width
            item->setGeometry(QRect(rect.x(), northHeight, rect.width(),
                        item->sizeHint().height()));
            //add to the north height
            northHeight += item->geometry().height()+spacing();
            
        } else if (position==South)
        {
            // QRect(int x, int y, int width, int height)
            item->setGeometry(QRect(item->geometry().x(), //keep the x
                                    item->geometry().y(), //keep the y
                                    rect.width(),        // set the new width
                                    item->sizeHint().height()));     // set the new height

            //add to the south height
            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(), //set x
                                    //set y = new y + new height -  (old height + spacing) + spacing
                                    rect.y() + rect.height() - southHeight + spacing(),
                                    item->geometry().width(),
                                    item->geometry().height()));
        }
        else if (position == Center)
        {
            center = wrapper;
        }

    } //endfor

    centerHeight = rect.height() - northHeight - southHeight;

    for (i = 0; i < list.size(); i++)
    {
        ItemWrapper * wrapper = list.at(i);
        QLayoutItem * item = wrapper->item;
        Position position = wrapper->position;

        if(position == West)
        {
            item->setGeometry(QRect(rect.x() + westWidth, //x position is new x size 
                              northHeight, //cached north height. 
                              item->sizeHint().width(), //width is whatever item wants
                              centerHeight)); // adjust for north and south height
            //adjust west width
            westWidth += item->geometry().width() + spacing();
        }
        else if(position == East)
        {
            item->setGeometry(QRect(item->geometry().x(), //keep x
                                    item->geometry().y(), //keep y
                                    item->sizeHint().width(),
                                    centerHeight)); //set new center height
            //add to east width
            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(rect.x() + rect.width() - eastWidth + spacing(),
                                    northHeight, //set the northHeight as y position
                                    item->geometry().width(),
                                    item->geometry().height()
                                    ));
        }
    }
    if (center)
        center->item->setGeometry( QRect(westWidth, // X
                                    northHeight,    // Y
                                    rect.width() - eastWidth - westWidth,
                                    centerHeight));
}

QSize BorderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}
QLayoutItem *BorderLayout::takeAt(int index)
{
    if (index >= 0 && index < list.size())
    {
        ItemWrapper *layoutStruct = list.takeAt(index);
        return layoutStruct->item;
    }
    return 0;
}

void BorderLayout::add(QLayoutItem *item, Position position)
{
    list.append(new ItemWrapper(item, position));
}

QSize BorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;

    for(int i = 0; i < list.size(); ++i)
    {
        ItemWrapper * wrapper = list.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if(sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else // sizeType == sizehint
            itemSize = wrapper->item->sizeHint();

        if(position == North || position == South || position == Center)
            totalSize.rheight() += itemSize.height();

        if(position == West || position == East || position == Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}


