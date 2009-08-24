/*
 * MidiController.h - A controller to receive MIDI control-changes
 *
 * Copyright (c) 2008 Paul Giblock <drfaygo/at/gmail.com>
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
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef _MIDI_CONTROLLER_H
#define _MIDI_CONTROLLER_H

#include <QtGui/QWidget>

#include "AutomatableModel.h"
#include "Controller.h"
#include "MidiEventProcessor.h"
#include "MidiPort.h"


class MidiPort;


class MidiController : public Controller, public MidiEventProcessor
{
	Q_OBJECT
public:
	MidiController( Model * _parent );
	virtual ~MidiController();

	virtual void processInEvent( const midiEvent & _me,
					const midiTime & _time );

	virtual void processOutEvent( const midiEvent& _me,
					const midiTime & _time)
	{
		// No output yet
	}

	virtual void saveSettings( QDomDocument & _doc, QDomElement & _this );
	virtual void loadSettings( const QDomElement & _this );
	virtual QString nodeName( void ) const;

	// Used by controllerConnectionDialog to copy
	void subscribeReadablePorts( const MidiPort::Map & _map );


public slots:
	virtual ControllerDialog * createDialog( QWidget * _parent );
	void updateName( void );


protected:
	// The internal per-controller get-value function
	virtual float value( int _offset );


	MidiPort m_midiPort;


	float m_lastValue;

	friend class ControllerConnectionDialog;
	friend class AutoDetectMidiController;

} ;


#endif
