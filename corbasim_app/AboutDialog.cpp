// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AboutDialog.cpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AboutDialog.hpp"
#include <corbasim/version.hpp>

using namespace corbasim::app;

namespace  
{
const char * corbasim_app_about_html = 
    "<html>"
    "<body>"
    "<h3>corbasim generic application</h3>"
    "<p>Version " CORBASIM_VERSION "</p>"
    "<p>Build " __DATE__ "</p>"
    "<p>Developed by: <li>"
        "<ul>Andr&eacute;s Senac &lt;andres@senac.es&gt;</ul>"
    "</li></p>"
    "</body>"
    "</html>";
} // namespace 

AboutDialog::AboutDialog(QWidget * parent) :
    QDialog(parent)
{
    resize(400, 200);
    
    QVBoxLayout * layout = new QVBoxLayout();

    m_textBrowser = new QTextBrowser();
    m_textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    m_textBrowser->setFrameShape(QFrame::NoFrame);
    m_textBrowser->setFrameShadow(QFrame::Plain);
    layout->addWidget(m_textBrowser);

    m_buttonBox = new QDialogButtonBox();
    m_buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    layout->addWidget(m_buttonBox);

    setLayout(layout);

    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setWindowTitle("About corbasim generic application");
    m_textBrowser->setHtml(corbasim_app_about_html);
}

AboutDialog::~AboutDialog()
{
}

