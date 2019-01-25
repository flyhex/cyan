/*
# Copyright Ole-André Rodlie.
#
# ole.andre.rodlie@gmail.com
#
# This software is governed by the CeCILL license under French law and
# abiding by the rules of distribution of free software. You can use,
# modify and / or redistribute the software under the terms of the CeCILL
# license as circulated by CEA, CNRS and INRIA at the following URL
# "https://www.cecill.info".
#
# As a counterpart to the access to the source code and rights to
# modify and redistribute granted by the license, users are provided only
# with a limited warranty and the software's author, the holder of the
# economic rights and the subsequent licensors have only limited
# liability.
#
# In this respect, the user's attention is drawn to the associated risks
# with loading, using, modifying and / or developing or reproducing the
# software by the user in light of its specific status of free software,
# that can mean that it is complicated to manipulate, and that also
# so that it is for developers and experienced
# professionals having in-depth computer knowledge. Users are therefore
# encouraged to test and test the software's suitability
# Requirements in the conditions of their systems
# data to be ensured and, more generally, to use and operate
# same conditions as regards security.
#
# The fact that you are presently reading this means that you have had
# knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef CYANLAYERTREEITEM_H
#define CYANLAYERTREEITEM_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>

#include <Magick++.h>

class CyanLayerTreeItem : public QTreeWidget, public QTreeWidgetItem
{
    Q_OBJECT

public:

    explicit CyanLayerTreeItem(QTreeWidget *parent = nullptr);
    ~CyanLayerTreeItem();

private:

    Magick::CompositeOperator _composite;
    int _id;
    QString _name;
    double _opacity;
    bool _visible;

public slots:

    Magick::CompositeOperator getComposite();
    void setComposite(Magick::CompositeOperator composite);
    int getLayerID();
    void setLayerID(int id);
    QString getLayerName();
    void setLayerName(QString name);
    double getOpacity();
    void setOpacity(double value);
    bool getVisibility();
    void setVisibility(bool visible);
};

#endif // CYANLAYERTREEITEM_H
