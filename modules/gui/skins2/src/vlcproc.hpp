/*****************************************************************************
 * vlcproc.hpp
 *****************************************************************************
 * Copyright (C) 2003 VideoLAN
 * $Id: vlcproc.hpp,v 1.4 2004/01/18 19:54:46 asmax Exp $
 *
 * Authors: Cyril Deguet     <asmax@via.ecp.fr>
 *          Olivier Teuli�re <ipkiss@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

#ifndef VLCPROC_HPP
#define VLCPROC_HPP

#include "../vars/playlist.hpp"
#include "../vars/time.hpp"
#include "../vars/volume.hpp"

class OSTimer;
class VarBool;


/// Singleton object handling VLC internal state and playlist
class VlcProc: public SkinObject
{
    public:
        /// Get the instance of VlcProc
        /// Returns NULL if the initialization of the object failed
        static VlcProc *instance( intf_thread_t *pIntf );

        /// Delete the instance of VlcProc
        static void destroy( intf_thread_t *pIntf );

        /// Getter for the playlist variable
        Playlist &getPlaylistVar() { return *((Playlist*)m_cPlaylist.get()); }

        /// Getter for the time variable
        Time &getTimeVar() { return *((Time*)(m_cVarTime.get())); }

        /// Getter for the volume variable
        Volume &getVolumeVar() { return *((Volume*)(m_cVarVolume.get())); }

        /// Getter for the mute variable
        VarBool &getIsMuteVar() { return *((VarBool*)(m_cVarMute.get())); }

        /// Getter for the playing variable
        VarBool &getIsPlayingVar() { return *((VarBool*)(m_cVarPlaying.get())); }

        /// Getter for the stopped variable
        VarBool &getIsStoppedVar() { return *((VarBool*)(m_cVarStopped.get())); }

        /// Getter for the paused variable
        VarBool &getIsPausedVar() { return *((VarBool*)(m_cVarPaused.get())); }

        /// Getter for the seekable variable
        VarBool &getIsSeekableVar() { return *((VarBool*)(m_cVarSeekable.get())); }

    protected:
        // Protected because it is a singleton
        VlcProc( intf_thread_t *pIntf );
        virtual ~VlcProc();

    private:
        /// Timer to call manage() regularly (via doManage())
        OSTimer *m_pTimer;
        /// Playlist variable
        VariablePtr m_cPlaylist;
        /// Variable for current position of the stream
        VariablePtr m_cVarTime;
        /// Variable for audio volume
        VariablePtr m_cVarVolume;
        /// Variable for the "mute" state
        VariablePtr m_cVarMute;
        /// Variables related to the input
        VariablePtr m_cVarPlaying;
        VariablePtr m_cVarStopped;
        VariablePtr m_cVarPaused;
        VariablePtr m_cVarSeekable;

        /// Poll VLC internals to update the status (volume, current time in
        /// the stream, current filename, play/pause/stop status, ...)
        /// This function should be called regurlarly, since there is no
        /// callback mechanism (yet?) to automatically update a variable when
        /// the internal status changes
        void manage();

        /// This function directly calls manage(), because it's boring to
        /// always write "pThis->"
        static void doManage( SkinObject *pObj );

        /// Callback for intf-change variable
        static int onIntfChange( vlc_object_t *pObj, const char *pVariable,
                                 vlc_value_t oldVal, vlc_value_t newVal,
                                 void *pParam );

        /// Callback for item-change variable
        static int onItemChange( vlc_object_t *pObj, const char *pVariable,
                                 vlc_value_t oldVal, vlc_value_t newVal,
                                 void *pParam );

        /// Callback for playlist-current variable
        static int onPlaylistChange( vlc_object_t *pObj, const char *pVariable,
                                     vlc_value_t oldVal, vlc_value_t newVal,
                                     void *pParam );
};


#endif
