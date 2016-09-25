/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "arrowinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QApplication>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <math.h>

ArrowInstrument::ArrowInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
    m_keyMod = 0;
}

void ArrowInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        mImageCopy = *imageArea.getImage();
        makeUndoCommand(imageArea);
    }
}

void ArrowInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        if (qApp->keyboardModifiers() & Qt::ShiftModifier || qApp->keyboardModifiers() & Qt::AltModifier){
            mEndPoint.setX(mStartPoint.x());
        }
        if (qApp->keyboardModifiers() & Qt::ControlModifier){
            mEndPoint.setY(mStartPoint.y());
        }
        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
    }
}

void ArrowInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

//void ArrowInstrument::keyPressEvent(QKeyEvent *event)
//{
//    m_keyMod = event->modifiers();
//}

//void ArrowInstrument::keyReleaseEvent(QKeyEvent *event)
//{
//    m_keyMod = 0;
//}

void ArrowInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    qreal width = 1.0;
    width = DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor();
    if(isSecondaryColor) {

        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            width,
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            width,
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    if(mStartPoint != mEndPoint)
    {
        painter.drawLine(mStartPoint, mEndPoint);
        // trdm
        double slopy , cosy , siny;
        double Par = 10.0 + width;  //length of Arrow (>)
        slopy = atan2( double( mStartPoint.y() - mEndPoint.y() ), double( mStartPoint.x() - mEndPoint.x() ) );
        cosy = cos( slopy );
        siny = sin( slopy ); //need math.h for these functions

        //http://www.ucancode.net/faq/VC-Example-Drawing-Arrow.htm
        QPoint m_Two;
        QPoint m_Two2;
        //here is the tough part - actually drawing the arrows
        //a total of 6 lines drawn to make the arrow shape

        m_Two.setX(mEndPoint.x() + int( Par * cosy - ( Par / 2.0 * siny ) ));
        m_Two.setY(mEndPoint.y() + int( Par * siny + ( Par / 2.0 * cosy ) ));
        painter.drawLine(m_Two,mEndPoint);

        m_Two2.setX(mEndPoint.x() + int( Par * cosy + Par / 2.0 * siny ));
        m_Two2.setY(mEndPoint.y() - int( Par / 2.0 * cosy - Par * siny ));
        painter.drawLine(m_Two2,mEndPoint);


        //here is the tough part - actually drawing the arrows
        //a total of 6 lines drawn to make the arrow shape
        /*
        pdc->MoveTo( m_One);
        pdc->LineTo( m_One.x + int( - Par * cosy - ( Par / 2.0 * siny ) ),
          m_One.y + int( - Par * siny + ( Par / 2.0 * cosy ) ) );
        pdc->LineTo( m_One.x + int( - Par * cosy + ( Par / 2.0 * siny ) ),
          m_One.y - int( Par / 2.0 * cosy + Par * siny ) );
        pdc->LineTo( m_One );
        */
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    imageArea.setEdited(true);
    //    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
    //                                                                 (mStartPoint.x() - mEndPoint.x()) +
    //                                                                 (mStartPoint.y() - mEndPoint.y()) *
    //                                                                 (mStartPoint.y() - mEndPoint.y()))));
    //    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    imageArea.update();
}
