//
//  config.h
//  InfinitDaemon
//
//  Created by infinit on 10/18/12.
//  Copyright (c) 2012 infinit. All rights reserved.
//

#ifndef InfinitDaemon_config_h
#define InfinitDaemon_config_h

# define INFINIT_DAEMON_VERSION         19
# define INFINIT_DAEMON_LABEL           @"io.infinit.InfinitDaemon"

# define INFINIT_FINDER_PLUGIN_NAME     @"FinderPlugin"
# define INFINIT_MACH_BUNBLE_STUB_NAME  @"mach_inject_bundle_stub"

// When defined, the window is shown on its own
// Otherwise, it is injected into the Finder
#define DEBUG_WITHOUT_FINDER

#endif
