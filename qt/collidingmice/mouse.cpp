/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

#define TO_DEG(x) x*(180/Pi)
static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

//! [0]
Mouse::Mouse(int number)
    : angle(0), speed(0), mouseEyeDirection(0),
      color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    number_m = number;
    angle_m = 90*number;
    rotate(angle_m);
}
//! [0]

//! [1]
QRectF Mouse::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}
//! [1]

//! [2]
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}
//! [2]

//! [3]
void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);
//
//    // Eyes
//    painter->setBrush(Qt::white);
//    painter->drawEllipse(-10, -17, 8, 8);
//    painter->drawEllipse(2, -17, 8, 8);
//
//    // Nose
//    painter->setBrush(Qt::black);
//    painter->drawEllipse(QRectF(-2, -22, 4, 4));
//
//    // Pupils
//    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
//    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));
//
//    // Ears
//    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
//    painter->drawEllipse(-17, -12, 16, 16);
//    painter->drawEllipse(1, -12, 16, 16);
//
//    // Tail
//    QPainterPath path(QPointF(0, 20));
//    path.cubicTo(-5, 22, -5, 22, 0, 25);
//    path.cubicTo(5, 27, 5, 32, 0, 30);
//    path.cubicTo(-5, 32, -5, 42, 0, 35);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawPath(path);
}
//! [3]

//! [4]
void Mouse::advance(int step)
{
    if (!step)
        return;
//! [4]
    // Don't move too far away
//! [5]
    QPointF p1 = QPointF(0,0);
    QPointF p2 = mapFromScene(0,0);
    QLineF lineToCenter(p1, p2);
    printf("mouse %d (%f,%f), (%f, %f) -- angle = %d\n", number_m, p1.x(), p1.y(), p2.x(), p2.y(), angle_m);
    qreal angleToCenter = ::acos(lineToCenter.dx() / lineToCenter.length());

    if (lineToCenter.length() >= 150) {
        printf("mouse %d: lineToCenter.dy() = %f, angleToCenter = %f\n", number_m, lineToCenter.dy(), TO_DEG(angleToCenter));
        if (lineToCenter.dy() < 0)
        {
            angleToCenter = TwoPi - angleToCenter;
            printf("lineToCenter.dy() < 0:...TwoPi - angleToCenter = %f\n", TO_DEG(angleToCenter));
        }

        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);
        printf("mouse %d: angle to center after normalizing %f\n", number_m, TO_DEG(angleToCenter));

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left if angle is between 45 and 180
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
            printf("--> mouse %d: rotating left angle: %f\n", number_m, angle);
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
            printf("--> mouse %d: rotating right angle: %f\n", number_m, angle);
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
//! [5] //! [6]
    }
//! [6]

    // Try not to crash with any other mice
//! [7]
    QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-30, -50)
                                                       << mapToScene(30, -50));
    foreach (QGraphicsItem *item, dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = ::acos(lineToMouse.dx() / lineToMouse.length());
        if (lineToMouse.dy() < 0)
        {
            //if object is on the X-axis.
            angleToMouse = TwoPi - angleToMouse;
        }
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
//! [7] //! [8]
        }
//! [8] //! [9]
    }
//! [9]

    // Add some random movement
//! [10]
    if (dangerMice.size() > 1 && (qrand() % 10) == 0) {
        if (qrand() % 1)
            angle += (qrand() % 100) / 500.0;
        else
            angle -= (qrand() % 100) / 500.0;
    }
//! [10]

//! [11]
    speed += (-50 + qrand() % 100) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    //rotate(dx);
    setPos(-150,0);
}
//! [11]
