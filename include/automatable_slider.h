/*
 * automatable_slider.h - class automatableSlider, a QSlider with automation
 *
 * Copyright (c) 2006 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */


#ifndef _AUTOMATABLE_SLIDER_H
#define _AUTOMATABLE_SLIDER_H

#include "qt3support.h"

#ifdef QT4

#include <QtGui/QSlider>

#else

#include <qslider.h>

#endif

#include "knob.h"




class automatableSlider : public QSlider
{
	Q_OBJECT
public:
	automatableSlider( QWidget * _parent, const QString & _name,
				engine * _engine, class track * _track );
	virtual ~automatableSlider();

	virtual void setRange( int _min, int _max );
	virtual void setValue( int _value );
	virtual void setInitValue( int _value );

	virtual void saveSettings( QDomDocument & _doc, QDomElement & _this,
							const QString & _name );
	virtual void loadSettings( const QDomElement & _this,
							const QString & _name );

	int logicValue( void );
	void clearAutomationValues( void );

	bool showStatus( void )
	{
		return( m_show_status );
	}


signals:
	void logicValueChanged( int _value );
	void logicSliderMoved( int _value );


protected:
	virtual void contextMenuEvent( QContextMenuEvent * _me );
	virtual void mousePressEvent( QMouseEvent * _me );
	virtual void mouseReleaseEvent( QMouseEvent * _me );
	virtual void wheelEvent( QWheelEvent * _me );


private:
	knob * m_knob;
	bool m_show_status;


private slots:
	void changeValue( int _value );
	void moveSlider( int _value );
	void updateSlider( void );

} ;




#endif
