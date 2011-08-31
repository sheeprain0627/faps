/*
 * MATLAB Compiler: 4.8 (R2008a)
 * Date: Wed Aug 31 22:28:25 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:facewarp" "-W"
 * "lib:facewarp" "-T" "link:lib" "FaceWarp.m" 
 */

#include "mclmcrrt.h"

#ifdef __cplusplus
extern "C" {
#endif
const unsigned char __MCC_facewarp_session_key[] = {
    'A', '6', 'A', 'C', 'A', '8', '9', '1', '1', '5', 'D', '0', '5', '1', 'F',
    '2', '4', 'F', 'E', '9', 'E', '2', '4', 'F', '5', '9', '6', 'D', 'A', '8',
    'E', '6', '2', 'B', 'E', '6', 'A', '1', '6', 'D', '3', '3', '7', 'F', 'C',
    'A', '8', '5', 'F', '6', '2', '2', '2', '4', 'B', '6', 'D', 'F', 'A', 'F',
    'A', '6', '4', '6', '1', '0', '9', 'A', '3', '8', 'A', '9', '4', 'C', '7',
    '0', '5', '5', '5', 'C', 'E', '1', '8', 'D', '6', '1', '0', '7', '6', 'B',
    'F', '4', '8', 'B', 'E', '3', '1', 'C', 'F', '5', '1', 'C', 'D', 'D', 'A',
    '8', 'B', 'E', 'D', '6', 'E', '9', 'B', 'F', 'C', 'F', 'D', '8', 'D', '3',
    '1', 'F', 'A', 'E', '0', 'B', '0', '6', '6', '4', '3', 'D', 'C', 'C', 'C',
    'E', '7', '8', '5', 'C', '9', 'A', '9', '9', '9', 'A', '6', '0', '8', 'D',
    '7', 'A', '0', '2', 'F', '5', 'D', '7', '2', '2', 'B', 'C', '5', '6', '7',
    'F', 'A', '3', '8', 'E', '6', '8', '6', 'C', '0', '1', '5', '7', '7', '3',
    '2', 'B', 'D', '3', '3', '8', 'A', 'B', '7', '7', '5', '2', '9', 'F', 'D',
    '9', 'E', '8', '0', '7', 'B', '2', 'A', 'F', '3', '0', '8', '7', 'E', '6',
    'A', '5', '4', '2', 'A', '3', '4', '9', 'A', 'E', '9', 'A', 'F', 'A', '6',
    '3', '0', 'E', 'A', 'E', '8', '6', 'A', '7', 'D', 'C', 'B', '5', 'C', '4',
    '2', '2', '1', 'E', '5', 'F', 'A', '0', '1', 'A', '7', '2', '5', '1', '2',
    '5', '\0'};

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
  "facewarp_310E6E1B09EF76DB5452CBC65428BE9B",

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


