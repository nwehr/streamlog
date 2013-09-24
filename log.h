#ifndef _log_log_h
#define _log_log_h

//
//		Copyright 2013 Nathan Wehr. All Rights Reserved.
//
//		Redistribution and use in source and binary forms, with or without
//		modification, are permitted provided that the following conditions are met:
//
//			1. Redistributions of source code must retain the above copyright notice, this
//			list of conditions and the following disclaimer.
//
//			2. Redistributions in binary form must reproduce the above copyright notice,
//			this list of conditions and the following disclaimer in the documentation
//			and/or other materials provided with the distribution.
//
//		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//		DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//		ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//		The views and conclusions contained in the software and documentation are those
//		of the authors and should not be interpreted as representing official policies,
//		either expressed or implied.
//

// C++
#include <forward_list>
#include <ostream>

namespace log {
	///////////////////////////////////////////////////////////////////////////////
	// basic_log
	///////////////////////////////////////////////////////////////////////////////
	class basic_log {
		basic_log( const basic_log& );
		basic_log& operator=( const basic_log& );
		
	public:
		basic_log();
		virtual ~basic_log();
		
		bool streams_available();
		
		void add_stream( std::ostream* );
		std::forward_list<std::ostream*>& streams();
		
		basic_log& log();
		
	protected:
		template<class T>
		basic_log& operator<<( T );
		
		template<class T>
		basic_log& operator<<( T (*)(T) );
		
	public:
		basic_log& operator<<( bool );
		basic_log& operator<<( short );
		basic_log& operator<<( unsigned short );
		basic_log& operator<<( int );
		basic_log& operator<<( unsigned int );
		basic_log& operator<<( long );
		basic_log& operator<<( unsigned long );
		basic_log& operator<<( float );
		basic_log& operator<<( double );
		basic_log& operator<<( void* );
		basic_log& operator<<( std::streambuf* );
		basic_log& operator<<( std::ostream& (*)(std::ostream&) );
		basic_log& operator<<( std::ios& (*)(std::ios&) );
		basic_log& operator<<( std::ios_base& (*)(std::ios_base&) );
		
	protected:
		bool m_streams_available;
		std::forward_list<std::ostream*> m_streams;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// severity_log : basic_log
	///////////////////////////////////////////////////////////////////////////////
	class severity_log : public basic_log {
		severity_log( const severity_log& );
		severity_log& operator=( const severity_log& );
		
	public:
		severity_log();
		virtual ~severity_log();
		
		void set_severity( int );
		
		severity_log& log( int );
		severity_log& operator()( int );
		
	private:
		int m_severity;
		
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// basic_log non-member functions
///////////////////////////////////////////////////////////////////////////////
template<class T>
log::basic_log& operator<<( log::basic_log&, T );

log::basic_log& operator<<( log::basic_log&, char );
log::basic_log& operator<<( log::basic_log&, signed char );
log::basic_log& operator<<( log::basic_log&, unsigned char );

log::basic_log& operator<<( log::basic_log&, const char* );
log::basic_log& operator<<( log::basic_log&, const signed char* );
log::basic_log& operator<<( log::basic_log&, const unsigned char* );

log::basic_log& operator<<( log::basic_log&, const std::string& );

#if defined( LOG_IMPL )
///////////////////////////////////////////////////////////////////////////////
// basic_log
///////////////////////////////////////////////////////////////////////////////
log::basic_log::basic_log()
: m_streams_available( true )
, m_streams( std::forward_list<std::ostream*>() )
{}

log::basic_log::~basic_log() {}

bool log::basic_log::streams_available() {
	return m_streams_available;
}

void log::basic_log::add_stream( std::ostream* i_stream ) {
	m_streams.push_front( i_stream );
}

std::forward_list<std::ostream*>& log::basic_log::streams() {
	return m_streams;
}

log::basic_log& log::basic_log::log() {
	m_streams_available = true;
	return *this;
}

template<class T>
log::basic_log& log::basic_log::operator<<( T i_val ) {
	if( m_streams_available ) {
		for( std::forward_list<std::ostream*>::iterator it = m_streams.begin(); it != m_streams.end(); ++it ) {
			(*it)->operator<<( i_val );
		}
		
	}
	
	return *this;
	
}

template<class T>
log::basic_log& log::basic_log::operator<<( T (*f)(T) ) {
	if( m_streams_available ) {
		for( std::forward_list<std::ostream*>::iterator it = m_streams.begin(); it != m_streams.end(); ++it ) {
			f( *(*it) );
		}
				
	}
	
	return *this;
	
}

log::basic_log& log::basic_log::operator<<( bool i_val ) {
	return operator<<<bool>( i_val );
}

log::basic_log& log::basic_log::operator<<( short i_val ) {
	return operator<<<short>( i_val );
}

log::basic_log& log::basic_log::operator<<( unsigned short i_val ) {
	return operator<<<unsigned short>( i_val );
}

log::basic_log& log::basic_log::operator<<( int i_val ) {
	return operator<<<int>( i_val );
}

log::basic_log& log::basic_log::operator<<( unsigned int i_val ) {
	return operator<<<unsigned int>( i_val );
}

log::basic_log& log::basic_log::operator<<( long i_val ) {
	return operator<<<long>( i_val );
}

log::basic_log& log::basic_log::operator<<( unsigned long i_val ) {
	return operator<<<unsigned long>( i_val );
}

log::basic_log& log::basic_log::operator<<( float i_val ) {
	return operator<<<float>( i_val );
}

log::basic_log& log::basic_log::operator<<( double i_val ) {
	return operator<<<double>( i_val );
}

log::basic_log& log::basic_log::operator<<( void* i_val ) {
	return operator<<<void*>( i_val );
}

log::basic_log& log::basic_log::operator<<( std::streambuf* i_val ) {
	return operator<<<std::streambuf*>( i_val );
}

log::basic_log& log::basic_log::operator<<( std::ostream& (*f)(std::ostream&) ) {
	return operator<<<std::ostream&>( f );
}

log::basic_log& log::basic_log::operator<<( std::ios& (*f)(std::ios&) ) {
	return operator<<<std::ios&>( f );
}

log::basic_log& log::basic_log::operator<<( std::ios_base& (*f)(std::ios_base&) ) {
	return operator<<<std::ios_base&>( f );
}

///////////////////////////////////////////////////////////////////////////////
// severity_log : basic_log
///////////////////////////////////////////////////////////////////////////////
log::severity_log::severity_log()
: m_severity( 0 )
{}

log::severity_log::~severity_log() {}

void log::severity_log::set_severity( int i_sev ) {
	m_severity = i_sev;
}

log::severity_log& log::severity_log::log( int i_sev ) {
	m_streams_available = (i_sev >= m_severity ? true : false);
	return *this;
}

log::severity_log& log::severity_log::operator()( int i_sev ) {
	m_streams_available = (i_sev >= m_severity ? true : false);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// basic_log non-member functions
///////////////////////////////////////////////////////////////////////////////
template<class T>
log::basic_log& operator<<( log::basic_log& i_log, T i_val ) {
	if( i_log.streams_available() ) {
		for( std::forward_list<std::ostream*>::iterator it = i_log.streams().begin(); it != i_log.streams().end(); ++it ) {
			operator<<( *(*it), i_val );
		}
		
	}
	
	return i_log;
	
}

log::basic_log& operator<<( log::basic_log& i_log, char i_val ) {
	return operator<<<char>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, signed char i_val ) {
	return operator<<<signed char>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, unsigned char i_val ) {
	return operator<<<unsigned char>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, const char* i_val ) {
	return operator<<<const char*>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, const signed char* i_val ) {
	return operator<<<const signed char*>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, const unsigned char* i_val ) {
	return operator<<<const unsigned char*>( i_log, i_val );
}

log::basic_log& operator<<( log::basic_log& i_log, const std::string& i_val ) {
	return operator<<<const std::string&>( i_log, i_val );
}

#endif // defined( LOG_IMPL )
#endif // _log_log_h
