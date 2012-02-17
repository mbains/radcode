#ifndef BORDERLAYOUT_H
#define BORDERLAYOUT_H

#include<QLayout>
#include<QRect>
#include<QWidgetItem>
class BorderLayout : public QLayout
{
public:
    enum Position { West, North, South, East, Center };

    // BorderLayout is a child object
    BorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
    BorderLayout(int spacing = -1);
    ~BorderLayout();

    //pure virtual
    void addItem(QLayoutItem *item);


    //different number of args than function of same name in QLayout
    void addWidget(QWidget *widget, Position position);
    
    //inherited,  virtual
    // Returns weather this layout can make use of more space than sizeHint()
    // a value of Qt::Verticle means it wants to grow in one direction
    virtual Qt::Orientations expandingDirections() const;

    //virtual
    //returns true if this layout's preferred height depends on its width
    //else false
    bool hasHeightForWidth() const;

    //pure virtual
    //return the number of items in the layout
    int count() const;

    //pure virtual
    //get item at index
    QLayoutItem *itemAt(int index) const;

    //pure virtual
    QSize minimumSize() const;

    //pure virtual
    // set geometry to rect
    void setGeometry(const QRect &rect);

    //pureVirtual
    //return preferred size
    QSize sizeHint() const;

    //inherited, pure virtual
    //remove item at index
    QLayoutItem *takeAt(int index);

    void add(QLayoutItem *item, Position p);

private:
    struct ItemWrapper
    {
        ItemWrapper(QLayoutItem *i, Position p)
        {
            item = i;
            position = p;
        }

    QLayoutItem *item;
    Position position;
    };
    enum SizeType { MinimumSize, SizeHint};
    QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper* > list;
};
#endif