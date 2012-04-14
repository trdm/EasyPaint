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

#ifndef PAINTINSTRUMENTS_H
#define PAINTINSTRUMENTS_H

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtCore/QPoint>
#include <QtGui/QImage>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Class for implementation of painting instruments.
 *
 */
class PaintInstruments : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param pImageArea A pointer to ImageArea.
     * @param parent Pointer for parent.
     */
    explicit PaintInstruments(ImageArea *pImageArea, QObject *parent = 0);
    ~PaintInstruments();

    inline void setStartPoint(const QPoint &point) { mStartPoint = point; }
    inline void setEndPoint(const QPoint &point) { mEndPoint = point; }

    /**
     * @brief Draw selection border.
     *
     * @param isSelected Flag shows is background image attached to selection area.
     *
     * @param isDrawBorders Flag shows is selection borders are need to be shown.
     */
    void selection(bool isSelected, bool isDrawBorders);
    /**
     * @brief Set selection image.
     *
     * @param image New selection image.
     */
    inline void setSelectionImage(const QImage &image) { mSelectionImage = image; }
    
private:
    ImageArea *mPImageArea; /**< A pointer to ImageArea. */
    QPoint mStartPoint, mEndPoint;
    QImage mSelectionImage;

signals:
    
public slots:
    
};

#endif // PAINTINSTRUMENTS_H
