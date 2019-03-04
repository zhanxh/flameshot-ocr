// Copyright(c) 2017-2018 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#include "bulletconfig.h"
#include "src/utils/colorutils.h"
#include "src/utils/pathinfo.h"
#include <QFontDatabase>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

BulletConfig::BulletConfig(QWidget *parent) : QWidget(parent) {
    m_layout = new QVBoxLayout(this);

    QComboBox *modesCB = new QComboBox();
    connect(fontsCB, &QComboBox::currentTextChanged,
            this, &TextConfig::fontFamilyChanged);
    fontsCB->addItems(fontDB.families());
    // TODO save family in config
    int index = fontsCB->findText(font().family());
    fontsCB->setCurrentIndex(index);


}
