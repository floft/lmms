/*
 * audio_port.h - base-class for objects providing sound at a port
 *
 * Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
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


#ifndef _AUDIO_PORT_H
#define _AUDIO_PORT_H

#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "mixer.h"

class effectChain;

class audioPort
{
public:
	audioPort( const QString & _name, bool _has_effect_chain = true );
	~audioPort();

	inline sampleFrame * firstBuffer( void )
	{
		return( m_firstBuffer );
	}

	inline sampleFrame * secondBuffer( void )
	{
		return( m_secondBuffer );
	}

	inline void lockFirstBuffer( void )
	{
		m_firstBufferLock.lock();
	}

	inline void lockSecondBuffer( void )
	{
		m_secondBufferLock.lock();
	}

	inline void unlockFirstBuffer( void )
	{
		m_firstBufferLock.unlock();
	}

	inline void unlockSecondBuffer( void )
	{
		m_secondBufferLock.unlock();
	}

	void nextPeriod( void );


	// indicate whether JACK & Co should provide output-buffer at ext. port
	inline bool extOutputEnabled( void ) const
	{
		return( m_extOutputEnabled );
	}

	void setExtOutputEnabled( bool _enabled );


	// next effect-channel after this audio-port
	// (-1 = none  0 = master)
	inline fx_ch_t nextFxChannel( void ) const
	{
		return( m_nextFxChannel );
	}

	inline effectChain * getEffects( void )
	{
		return( m_effects );
	}

	void setNextFxChannel( const fx_ch_t _chnl )
	{
		m_nextFxChannel = _chnl;
	}


	const QString & name( void ) const
	{
		return( m_name );
	}

	void setName( const QString & _new_name );


	bool processEffects( void );


	enum bufferUsages
	{
		NoUsage,
		FirstBuffer,
		BothBuffers
	} ;


private:
	volatile bufferUsages m_bufferUsage;

	sampleFrame * m_firstBuffer;
	sampleFrame * m_secondBuffer;
	QMutex m_firstBufferLock;
	QMutex m_secondBufferLock;

	bool m_extOutputEnabled;
	fx_ch_t m_nextFxChannel;

	QString m_name;
	
	effectChain * m_effects;


	friend class mixer;
	friend class MixerWorkerThread;

} ;


#endif
