#pragma once

#include "ofMain.h"
#include "ofGstVideoPlayer.h"
#include <gst/net/gstnet.h>
#include "ofxOsc.h"

class ofxGstVideoSyncPlayer{

    public:

        ofxGstVideoSyncPlayer();
        ~ofxGstVideoSyncPlayer();

        void                            init( const std::string _clockIP, const unsigned int _clockPort, bool _isMaster = false );
        bool                            load( std::string _path );
        void                            play();
        void                            update();
        void                            draw( ofPoint _pos, float _width = -1, float _height = -1 );
        void                            drawSubsection( float _x, float _y, float _w, float _h, float _sx, float _sy );
        void                            loop( bool _loop );
        void                            setVolume( float _volume );
        float                           getWidth();
        float                           getHeight();
        void                            pause();
        ofTexture                       getTexture();
        bool                            isPaused();
        bool                            isMovieEnded();
 
    private:
        
        void                            setMasterClock();
        void                            setClientClock( GstClockTime _baseTime );

        void                            sendPauseMsg();
        void                            sendPlayMsg();
        void                            sendLoopMsg();

        void                            movieEnded( ofEventArgs & e );

    private:

        GstClock*                       m_gstClock;         ///> The network clock.
        GstElement*                     m_gstPipeline;      ///> The running pipeline.
        GstClockTime                    m_gstClockTime;     ///> The base time.
        shared_ptr<ofGstVideoPlayer>    m_gstPlayer;        ///> The gstreamer player.
        ofVideoPlayer                   m_videoPlayer;      ///> Our OF video player.
        bool                            m_isMaster;         ///> Is the master?
        std::string                     m_clockIP;          ///> The IP of the server.
        unsigned int                    m_clockPort;        ///> The port that should be used for the synchronization.
        unsigned int                    m_rcvPort;          ///> osc communication.
        unsigned int                    m_sndPort;          ///> osc communication.
        std::vector<string>             m_connectedClients; ///> Our connected clients.
        shared_ptr<ofxOscSender>        m_oscSender;        ///> osc sender.
        shared_ptr<ofxOscReceiver>      m_oscReceiver;      ///> osc receiver.
        bool                            m_loop;             ///> Should we loop?
        bool                            m_initialized;      ///> If the player initialized properly ??
        bool                            m_movieEnded;       ///> Has the video ended??
        gint64                          m_pos;              ///> Position of the player.
        bool                            m_paused;           ///> Is the player paused ??
};
