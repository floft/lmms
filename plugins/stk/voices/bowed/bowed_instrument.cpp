/*
 *
 * Copyright (c) 2008 Danny McRae <khjklujn/at/users.sourceforge.net>
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


#include "engine.h"
#include "note_play_handle.h"

#include "bowed_instrument.h"
#include "bowed_instrument_view.h"
#include "bowed_processor.h"

#undef SINGLE_SOURCE_COMPILE
#include "embedded_resources.h"


extern "C"
{

plugin::descriptor bowed_plugin_descriptor =
{
	STRINGIFY_PLUGIN_NAME( PLUGIN_NAME ),
	"Bowed",
	QT_TRANSLATE_NOOP( "pluginBrowser",
				"Bowed string" ),
	"Danny McRae <khjklujn/at/users.sf.net>",
	0x0100,
	plugin::Instrument,
	new QPixmap( PLUGIN_NAME::getIconPixmap( "logo" ) ),
	NULL
} ;

}


bowedInstrument::bowedInstrument( instrumentTrack * _channel_track ):
	stkInstrument<bowedProcessor, bowedModel>( _channel_track, &bowed_plugin_descriptor )
{
	model()->bowPressure()->setTrack( _channel_track );
	model()->bowPosition()->setTrack( _channel_track );
	model()->vibratoFrequency()->setTrack( _channel_track );
	model()->vibratoGain()->setTrack( _channel_track );
}




bowedInstrument::~bowedInstrument()
{
}




QString bowedInstrument::nodeName( void ) const
{
	return( bowed_plugin_descriptor.name );
}




pluginView * bowedInstrument::instantiateView( QWidget * _parent )
{
	return( new bowedInstrumentView( this, _parent ) );
}




extern "C"
{

// neccessary for getting instance out of shared lib
plugin * lmms_plugin_main( model * _model, void * _data )
{
	return( new bowedInstrument( static_cast<instrumentTrack *>( _data ) ) );
}


}


