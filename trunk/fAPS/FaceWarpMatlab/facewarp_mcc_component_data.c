/*
 * MATLAB Compiler: 4.8 (R2008a)
 * Date: Thu Sep 01 01:07:25 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:facewarp" "-W"
 * "lib:facewarp" "-T" "link:lib" "FaceWarp.m" 
 */

#include "mclmcrrt.h"

#ifdef __cplusplus
extern "C" {
#endif
const unsigned char __MCC_facewarp_session_key[] = {
    'B', 'E', '8', '3', '4', 'C', '1', 'C', 'D', '6', '3', '7', '0', '6', 'D',
    'C', 'B', 'A', '4', 'A', 'A', 'D', '2', 'B', 'B', '9', '0', 'B', 'A', 'C',
    '8', 'B', '9', 'C', '4', 'D', '8', 'C', '9', '2', '3', '3', 'F', 'A', '2',
    'A', 'D', '1', '2', 'A', '1', '2', '3', 'C', 'C', 'B', '0', '1', '5', '0',
    'B', '3', '2', '0', '6', 'E', 'D', 'E', 'F', '8', '5', 'B', 'D', 'C', '1',
    '8', 'A', '8', 'D', '6', '4', '8', '7', '4', '2', '0', 'F', 'B', 'D', '4',
    '7', '6', 'F', '9', '6', 'E', '9', 'C', '1', '7', 'A', 'C', '5', 'F', '0',
    '6', '8', 'B', '2', 'D', '8', '5', 'F', '6', '0', 'B', '2', '4', 'A', 'E',
    '9', '4', '3', 'B', 'B', '4', 'D', '7', '6', 'C', '0', '9', '7', 'D', 'D',
    '6', '6', '8', '5', '0', '9', '8', '8', '0', 'E', 'D', 'A', 'E', 'F', '5',
    '9', '1', 'C', 'A', 'E', '7', '8', '3', '5', '2', '7', '8', 'D', 'D', 'D',
    'B', '7', '3', '5', '1', '3', 'A', 'C', '4', '4', '3', 'D', '7', '8', 'F',
    '5', 'D', 'E', '4', 'B', '0', 'A', 'C', 'F', '4', 'D', '0', '8', 'D', 'D',
    'D', '7', 'A', 'E', '6', '2', '3', '9', '1', '0', '2', '9', '0', '7', '2',
    '5', '2', '5', '7', '7', 'D', '1', '3', '0', '7', '2', 'E', 'A', '3', '4',
    'C', '0', 'A', '5', '0', '3', 'F', 'D', '4', '2', 'C', 'A', '7', 'E', '8',
    '1', '3', '2', 'F', 'C', '6', '6', '5', 'D', '6', 'B', 'A', 'A', 'A', 'E',
    'D', '\0'};

const unsigned char __MCC_facewarp_public_key[] = {
    '3', '0', '8', '1', '9', 'D', '3', '0', '0', 'D', '0', '6', '0', '9', '2',
    'A', '8', '6', '4', '8', '8', '6', 'F', '7', '0', 'D', '0', '1', '0', '1',
    '0', '1', '0', '5', '0', '0', '0', '3', '8', '1', '8', 'B', '0', '0', '3',
    '0', '8', '1', '8', '7', '0', '2', '8', '1', '8', '1', '0', '0', 'C', '4',
    '9', 'C', 'A', 'C', '3', '4', 'E', 'D', '1', '3', 'A', '5', '2', '0', '6',
    '5', '8', 'F', '6', 'F', '8', 'E', '0', '1', '3', '8', 'C', '4', '3', '1',
    '5', 'B', '4', '3', '1', '5', '2', '7', '7', 'E', 'D', '3', 'F', '7', 'D',
    'A', 'E', '5', '3', '0', '9', '9', 'D', 'B', '0', '8', 'E', 'E', '5', '8',
    '9', 'F', '8', '0', '4', 'D', '4', 'B', '9', '8', '1', '3', '2', '6', 'A',
    '5', '2', 'C', 'C', 'E', '4', '3', '8', '2', 'E', '9', 'F', '2', 'B', '4',
    'D', '0', '8', '5', 'E', 'B', '9', '5', '0', 'C', '7', 'A', 'B', '1', '2',
    'E', 'D', 'E', '2', 'D', '4', '1', '2', '9', '7', '8', '2', '0', 'E', '6',
    '3', '7', '7', 'A', '5', 'F', 'E', 'B', '5', '6', '8', '9', 'D', '4', 'E',
    '6', '0', '3', '2', 'F', '6', '0', 'C', '4', '3', '0', '7', '4', 'A', '0',
    '4', 'C', '2', '6', 'A', 'B', '7', '2', 'F', '5', '4', 'B', '5', '1', 'B',
    'B', '4', '6', '0', '5', '7', '8', '7', '8', '5', 'B', '1', '9', '9', '0',
    '1', '4', '3', '1', '4', 'A', '6', '5', 'F', '0', '9', '0', 'B', '6', '1',
    'F', 'C', '2', '0', '1', '6', '9', '4', '5', '3', 'B', '5', '8', 'F', 'C',
    '8', 'B', 'A', '4', '3', 'E', '6', '7', '7', '6', 'E', 'B', '7', 'E', 'C',
    'D', '3', '1', '7', '8', 'B', '5', '6', 'A', 'B', '0', 'F', 'A', '0', '6',
    'D', 'D', '6', '4', '9', '6', '7', 'C', 'B', '1', '4', '9', 'E', '5', '0',
    '2', '0', '1', '1', '1', '\0'};

static const char * MCC_facewarp_matlabpath_data[] = 
  { "facewarp/", "toolbox/compiler/deploy/", "$TOOLBOXMATLABDIR/general/",
    "$TOOLBOXMATLABDIR/ops/", "$TOOLBOXMATLABDIR/lang/",
    "$TOOLBOXMATLABDIR/elmat/", "$TOOLBOXMATLABDIR/elfun/",
    "$TOOLBOXMATLABDIR/specfun/", "$TOOLBOXMATLABDIR/matfun/",
    "$TOOLBOXMATLABDIR/datafun/", "$TOOLBOXMATLABDIR/polyfun/",
    "$TOOLBOXMATLABDIR/funfun/", "$TOOLBOXMATLABDIR/sparfun/",
    "$TOOLBOXMATLABDIR/scribe/", "$TOOLBOXMATLABDIR/graph2d/",
    "$TOOLBOXMATLABDIR/graph3d/", "$TOOLBOXMATLABDIR/specgraph/",
    "$TOOLBOXMATLABDIR/graphics/", "$TOOLBOXMATLABDIR/uitools/",
    "$TOOLBOXMATLABDIR/strfun/", "$TOOLBOXMATLABDIR/imagesci/",
    "$TOOLBOXMATLABDIR/iofun/", "$TOOLBOXMATLABDIR/audiovideo/",
    "$TOOLBOXMATLABDIR/timefun/", "$TOOLBOXMATLABDIR/datatypes/",
    "$TOOLBOXMATLABDIR/verctrl/", "$TOOLBOXMATLABDIR/codetools/",
    "$TOOLBOXMATLABDIR/helptools/", "$TOOLBOXMATLABDIR/winfun/",
    "$TOOLBOXMATLABDIR/demos/", "$TOOLBOXMATLABDIR/timeseries/",
    "$TOOLBOXMATLABDIR/hds/", "$TOOLBOXMATLABDIR/guide/",
    "$TOOLBOXMATLABDIR/plottools/", "toolbox/local/",
    "toolbox/shared/dastudio/", "$TOOLBOXMATLABDIR/datamanager/",
    "toolbox/comm/comm/", "toolbox/compiler/", "toolbox/shared/optimlib/",
    "toolbox/database/database/", "toolbox/images/images/",
    "toolbox/images/iptutils/", "toolbox/shared/imageslib/",
    "toolbox/images/medformats/", "toolbox/shared/spcuilib/",
    "toolbox/signal/sigtools/" };

static const char * MCC_facewarp_classpath_data[] = 
  { "java/jar/toolbox/database.jar", "java/jar/toolbox/images.jar" };

static const char * MCC_facewarp_libpath_data[] = 
  { "" };

static const char * MCC_facewarp_app_opts_data[] = 
  { "" };

static const char * MCC_facewarp_run_opts_data[] = 
  { "" };

static const char * MCC_facewarp_warning_state_data[] = 
  { "off:MATLAB:dispatcher:nameConflict" };


mclComponentData __MCC_facewarp_component_data = { 

  /* Public key data */
  __MCC_facewarp_public_key,

  /* Component name */
  "facewarp",

  /* Component Root */
  "",

  /* Application key data */
  __MCC_facewarp_session_key,

  /* Component's MATLAB Path */
  MCC_facewarp_matlabpath_data,

  /* Number of directories in the MATLAB Path */
  47,

  /* Component's Java class path */
  MCC_facewarp_classpath_data,
  /* Number of directories in the Java class path */
  2,

  /* Component's load library path (for extra shared libraries) */
  MCC_facewarp_libpath_data,
  /* Number of directories in the load library path */
  0,

  /* MCR instance-specific runtime options */
  MCC_facewarp_app_opts_data,
  /* Number of MCR instance-specific runtime options */
  0,

  /* MCR global runtime options */
  MCC_facewarp_run_opts_data,
  /* Number of MCR global runtime options */
  0,
  
  /* Component preferences directory */
  "facewarp_DD81E699A1DA3AB1A944B135EC64F735",

  /* MCR warning status data */
  MCC_facewarp_warning_state_data,
  /* Number of MCR warning status modifiers */
  1,

  /* Path to component - evaluated at runtime */
  NULL

};

#ifdef __cplusplus
}
#endif


