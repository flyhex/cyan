/*
#
# Cyan <https://cyan.fxarena.net>
# Copyright Ole-André Rodlie, FxArena DA.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
*/

#ifndef CYANLAYERWIDGET_H
#define CYANLAYERWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QMdiSubWindow>
#include <QToolBar>

#include <Magick++.h>

#include "CyanLayerTree.h"

#include "CyanGlobal.h"

class CYANSHARED_EXPORT CyanLayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CyanLayerWidget(QWidget *parent = nullptr,
                             bool native = false);
    ~CyanLayerWidget();

signals:
    void layerCompositeChanged(const Magick::CompositeOperator &composite,
                               const int &id);
    void layerOpacityChanged(const double &value,
                             const int &id);
    void selectedLayer(int id);
    void layerVisibilityChanged(int id, bool visible);
    void layerLabelChanged(int id, QString label);
    void layerLockChanged(int id, bool lock);
    void moveLayerEvent(QKeyEvent *e);
    void newLayer(bool text);
    void removeLayer(int id);
    void moveLayerUp(int id);
    void moveLayerDown(int id);
    void duplicateLayer(int id);

public slots:
    void setCanvasID(const QString &id);
    const QString getCanvasID();
    CyanLayerTreeItem* getCurrentLayer();
    void setCurrentLayer(const int &id);
    void handleTabActivated(QMdiSubWindow *tab,
                            bool force = false);
    void clearTree();
    void setTextSupport(bool enabled);
    void moveCurrentLayerUp(bool triggered);
    void moveCurrentLayerDown(bool triggered);
    void duplicateCurrentLayer(bool triggered);
    void removeCurrentLayer(bool triggered);
    void createNewLayer(bool triggered);

private:
    LayerTree *layerTree;
    QComboBox *layerCompositeBox;
    //QSlider *layerOpacitySlider;
    QDoubleSpinBox *layerOpacitySpin;
    bool _textSupport;
    QToolBar *actionBar;

private slots:
    void populateCompositeBox();
    void handleLayerActivated(QTreeWidgetItem *item,
                              int col);
    void handleLayerActivated(QTreeWidgetItem *item,
                              QTreeWidgetItem *old);
    void handleLayerOpacitySpin(double value);
    void handleLayerOpacitySlider();
    void handleLayerCompositeBox();
    void handleTreeSelectedLayer(int id);
    void handleTreeLayerVisibility(int id,
                                   bool visible);
    void handleTreeLayerLabel(int id,
                              QString label);
    void handleTreeLayerLock(int id,
                             bool lock);
    void handleTreeMoveLayer(QKeyEvent *e);
    void handleNewImageLayer();
    void handleNewTextLayer();
    void handleRemoveLayer();
    void handleMoveLayerUp();
    void handleMoveLayerDown();
    void handleDuplicateLayer();
};

#endif // CYANLAYERWIDGET_H
