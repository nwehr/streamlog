//
//  main.cpp
//  log
//
//  Created by Nathan Wehr on 9/23/13.
//  Copyright (c) 2013 Creltek. All rights reserved.
//

#include <iostream>

#define LOG_IMPL
#include <log/log.h>

int main( int argc, const char* argv[] ) {
	log::severity_log MyLog;
	
	MyLog.add_stream( &std::cout );
	MyLog.set_severity( 2 );
		
	MyLog( 2 ) << "Hello, World!" << std::endl;
	
}
