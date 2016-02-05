#ifndef WANDERINGHORSE_NET_V8_NC_NCSTREAM_HPP_INCLUDED
#define WANDERINGHORSE_NET_V8_NC_NCSTREAM_HPP_INCLUDED 1

#include <ncurses.h>

#include <iostream>

namespace nc {

	/**
	   A very basic streambuffer which sends all of it's input to
	   a given curses WINDOW. It does no buffering at all, sending
	   it's input byte-by-byte. It is intended to be used as a
	   replacement for the streambuffer owned by
	   eshell::ostream().

	   Note that using two streambuffers on the same stream will
	   not work: only the last one installed will send any output,
	   and there's NO TELLING what sending output to the other
	   will do.

	   Sending more than one stream to one WINDOW is fine, and
	   unsigned long argument to the ctors is intended just for this case.
	*/
	class nc_window_streambuf : public std::streambuf
	{
	private:
		WINDOW * m_pnl;
		unsigned long m_flags;
		std::ostream * m_os;
		std::streambuf * m_old;
		void copy( const nc_window_streambuf & rhs );
    int m_count_lines;
	public:
		/**
		   Implants this object as os's rdbuf(). When this
		   object is destroyed, the previous rdbuf() is
		   restored.

		   p and os must both outlive this object.

		   If curses_attr is non-zero then those
		   attributes are set on p before each write
		   and turned off after each write. This is useful
		   when mapping multiple streams to one pad.

		   scrollok(p,true) is called because:

		   a) that is (almost?) always the desired behaviour
		   for this class.

		   b) if waddch(p) ever fails, as it "might" when
		   scrolling is disabled (untested), then os will be
		   marked as "done" by the iostreams framework and
		   won't be usable for output any more.
		*/
		nc_window_streambuf( WINDOW * p,
				      std::ostream & os,
				      unsigned long curses_attr = 0 );

		/**
		   Identical to the 3-arg constructor except
		   that it has no assosciated stream from
		   which it will receive input. The client should
		   call:

<pre>
		   std::streambuf * old = mystream.rdbuf();
		   mystream.rdbuf( mync_window_streambuf );
</pre>

		   to rediect output sent to mystream to p, and should
		   call mystream.rdbuf(old) to restore the stream's
		   old buffer when the client is finished. This is
		   tedious and error-prone, and is provided mainly so
		   that classes like NCStreamPad can use this class
		   more sensibly by managing the reassigment of
		   this streambuffer themselves.
		*/
		nc_window_streambuf( WINDOW * p,
				      unsigned long curses_attr = 0 );


		nc_window_streambuf( const nc_window_streambuf & rhs );
		nc_window_streambuf & operator=( const nc_window_streambuf & rhs );
		/**
		   If this object was constructed with a target
		   stream, this restores that stream's rdbuf() to its
		   pre-ctor state. If no stream was assigned then
		   this function does nothing.
		*/
		virtual ~nc_window_streambuf();
		/**
		   Sends c to this object's panel.

		   If c is EOF or std::isspace(c) then sync() is called.

		   Potential TODO: write io manipulators
		   to toggle curses attributes??? Would be
		   cool, but sounds tedious.

		   Returns c on success and EOF if sync() returns EOF
		   or if waddch() returns ERR.
		*/
		virtual int overflow( int c );

		/**
		   If (panel_below(0)) then:

		   Calls update_panels() and doupdate(). Older
		   behaviour turns out to hose panels.

		   Otherwise:

		   Calls wrefresh() on this object's window.  Returns 0
		   unless refresh() returns curses' ERR, in which case
		   this function returns EOF.
		*/
		virtual int sync();
    
    int GetLineCount()
    {
      return m_count_lines;
    }
	};



} // namespace


#endif // WANDERINGHORSE_NET_V8_NC_NCSTREAM_HPP_INCLUDED
