#pragma once /*SKIP_LINE_IN_GRAMMAR_GENERATOR*/
const char* kGenCadFileBnf = /*SKIP_LINE_IN_GRAMMAR_GENERATOR*/ R"MultiLineString(
s                   : /[ \t]/ ;
n                   : /\r?\n/ ;
sign                : '+' | '-' ;
number              : /[-+]?[0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?/ ;
p_integer           : <sign>? /[0-9]+/ ;
string              : '"' /[^"]*/ '"' ;
nonquoted_string    : /[^\"\s\r\n]+/;
string_to_end       : /[^\r\n$]*/;
wrapper_to_end      : (<string>|<string_to_end>);
arc_start           : <x_y_ref> ;
arc_end             : <x_y_ref> ;
arc_center          : <x_y_ref> ;
arc_p1              : <number> ;
arc_p2              : <number> ;
arc_ref             : <arc_start> <s>+ <arc_end> <s>+ <arc_center> <s>* <arc_p1>? <s>* <arc_p2>?;
artwork_name        : <string> ;
attribute_category  : <nonquoted_string> ;
attribute_name      : (<nonquoted_string>|<string>) ;
attribute_data      : <wrapper_to_end> ;
radius              : <number>;
circle_ref          : <x_y_ref> <s>+ <radius> <s>*;
component_name      : (<nonquoted_string>|<string>);
dimension           : ("INCH" | "THOU" | "MM" | "MM100" | ("USER" <s> <p_integer>) | ("USERM" <s> <p_integer>) | ("USERMM" <s> <p_integer>));
drill_size          : <number>;
fid_name            : (<nonquoted_string>|<string>);
filename            : <string>;
filled_ref          : ("0" | "YES");
flip                : ("0" | "FLIP");
height              : <number>;
width               : <number>;
layer_index         : <p_integer>;
layer               : ("TOP"|"BOTTOM"|"SOLDERMASK_TOP"|"SOLDERMASK_BOTTOM"|"SILKSCREEN_TOP"|"SILKSCREEN_BOTTOM"|"SOLDERPASTE_TOP"|"SOLDERPASTE_BOTTOM"|("POWER" <layer_index>)|("GROUND" <layer_index>)|("INNER" <layer_index>?)|"ALL"|("LAYER" <layer_index>)|("LAYER_" <layer_index>)|("LAYERSET" <layer_index>));
line_start          : <x_y_ref>;
line_end            : <x_y_ref>;
line_ref            : <line_start> <s>+ <line_end>;
mirror              : ("0"|"MIRRORX"|"MIRRORY");
pad_name            : (<nonquoted_string>|<string>);
pad_type            : ("FINGER"|"ROUND"|"ANNULAR"|"BULLET"|"RECTANGULAR"|"HEXAGON"|"OCTAGON"|"POLYGON"|"UNKNOWN");
part_name           : (<nonquoted_string>|<string>);
pin_name            : (<nonquoted_string>|<string>);
probe               : <string>;
rectangle_ref       : <x_y_ref> <s>+ <width> <s>+ <height>;
rot                 : <number>;
shape_name          : (<nonquoted_string>|<string>);
sig_name            : (<nonquoted_string>|<string>);
tan                 : <string>;
testpad_name        : <string>;
text_size           : <number>;
text_text           : <string>;
text_par            : <text_size> <s>+ <rot> <s>+ <mirror> <s>+ <layer> <s>+ <text_text> <s>+ <rectangle_ref>;
tp_name             : <string>;
track_name          : <nonquoted_string>;
track_width         : <number>;
via_name            : <nonquoted_string>;
x                   : <number> ;
y                   : <number> ;
x_y_ref             : <x> <s>+ <y>;
header              : "$HEADER" <n> <gencad_version>? <user>? <drawing>? <revision>? <units>? <origin>? <intertrack>? <attribute>* "$ENDHEADER" <n>*;
major               : <p_integer>;
minor               : <p_integer>;
gencad_version      : "GENCAD" <s>+ <major> "." <minor>  <n>;
user                : "USER" <s>+ <wrapper_to_end> <n>;
drawing             : "DRAWING" <s>+ <wrapper_to_end> <n>;
revision            : "REVISION" <s>+ <wrapper_to_end> <n>;
unit                : <dimension>;
units               : "UNITS" <s>+ <unit> <n>;
origin              : "ORIGIN" <s>+ <x_y_ref> <n>;
intertrack          : "INTERTRACK" <s>+ <number> <n>;
attribute           : "ATTRIBUTE" <s>+ <attribute_category> <s>+ <attribute_name> <s>+ <attribute_data> <n>;
name                : /[^\s\t\r\n$]*/;
thickness           : "THICKNESS" <s>+ <number> <n>;
line                : "LINE" <s>+ <line_ref> <n>;
arc                 : "ARC" <s>+ <arc_ref> <n>;
circle              : "CIRCLE" <s>+ <circle_ref> <n>;
rectangle           : "RECTANGLE" <s>+ <x> <s>+ <y>  <s>+ <width> <s>+ <height> <n>;
cutout              : "CUTOUT" <s>+ <name> <s>+ <n> (<line>|<arc>|<circle>|<rectangle>|<n>)*;
mask                : "MASK" <s>+ <name> <s>+ <layer> <n> (<line>|<arc>|<circle>|<rectangle>|<n>)*;
artwork             : "ARTWORK" <s>+ <name> <s>+ <layer> <n> (<line>|<arc>|<circle>|<rectangle>|<type>|<filled>)*;
board               : "$BOARD" <n> <thickness>? (<line>|<arc>|<circle>|<rectangle>)* (<cutout>|<mask>|<artwork>|<attribute>)* <n>* "$ENDBOARD" <n>*;
pad                 : "PAD" <s>+ <pad_name> <s>+ <pad_type> <s>+ <drill_size> <n> (<line>|<arc>|<circle>|<rectangle>|<attribute>)* <n>*;
pads                : "$PADS" <n> <pad>* "$ENDPADS" <n>*;
padstacks_pad       : "PAD" <s>+ <pad_name> <s>+ <layer> <s>+ <rot> <s>+ <mirror> <n>;
padstack            : "PADSTACK" <s>+ <pad_name> <s>+ <drill_size> <n>* <padstacks_pad>* <attribute>*;
padstacks           : "$PADSTACKS" <n> <padstack>* "$ENDPADSTACKS" <n>*;
layer_name          : <nonquoted_string>;
named_layer         : "LAYER" <s>+ <layer_name> <n>*;
filled              : "FILLED" <s>+ <filled_ref> <n>*;
text                : "TEXT" <s>+ <x_y_ref> <s>+ <text_par> <n>*;
artworks_artwork    : "ARTWORK" <artwork_name> <n> (<named_layer>|<track_>|<filled>|<text>|<line>|<arc>|<circle>|<rectangle>|<attribute>)* <n>*;
artworks            : "$ARTWORKS" <n>* <artworks_artwork>* "$ENDARTWORKS" <n>*;
fiducial            : "FIDUCIAL" <s>+ <x_y_ref> <n>;
insert              : "INSERT" <s>+ <nonquoted_string> <n>;
height_             : "HEIGHT" <s>+ <height> <n>;
shape_artwork       : "ARTWORK" <s>+ <artwork_name> <s> <x_y_ref> <s> <rot> <s> <mirror> <n> <attribute>*;
fid                 : "FID" <s>+ <fid_name> <s> <pad_name> <s> <x_y_ref> <s> <layer> <s> <rot> <s> <mirror> <n> <attribute>*;
shape_pin_name      : (<nonquoted_string>|<string>);
shapes_pin          : "PIN" <s>+ <shape_pin_name> <s>+ <pad_name> <s> <x_y_ref> <s> <layer> <s> <rot> <s> <mirror> <n>;
shape               : "SHAPE" <s>+ <shape_name> <n> (<line>|<arc>|<circle>|<rectangle>|<fiducial>|<insert>|<height_>|<attribute>|<shape_artwork>|<fid>|<shapes_pin>)* <n>*;
shapes              : "$SHAPES" <n>* <shape>* "$ENDSHAPES" <n>*;
device_name         : <wrapper_to_end>;
device_             : "DEVICE" <s>+ <device_name> <n>*;
place               : "PLACE" <s>+ <x_y_ref> <n>;
rotation            : "ROTATION" <s>+ <rot> <n>;
shape_              : "SHAPE" <s>+ <shape_name> <s>+ <mirror> <s>+ <flip> <n>;
artwork_            : "ARTWORK" <s>+ <artwork_name> <s>+ <x_y_ref> <s>+ <rot> <s>+ <mirror> <s>+ <flip> <n> <attribute>*;
sheet               : "SHEET" <s>+ <string> <n>*;
component           : "COMPONENT" <s>+ <component_name> <n>* (<device_>|<place>|<named_layer>|<rotation>|<shape_>|<value>|<partnumber>|<artwork_>|<fid>|<text>|<sheet>|<attribute>)* <n>*;
components          : "$COMPONENTS" <n>* <component>* "$ENDCOMPONENTS" <n>*;
part                : "PART" <s>+ <part_name> <n>;
type                : "TYPE" <s>+ (<nonquoted_string>|<string>) <n>;
style               : "STYLE" <s>+ <string> <n>*;
package             : "PACKAGE" <s>+ <string> <n>*;
pindesc             : "PINDESC" <s>+ <pin_name> <s> <string> <n>*;
pinfunct            : "PINFUNCT" <s>+ <pin_name> <s> <string> <n>*;
pincount            : "PINCOUT" <s>+ <number> <n>*;
tol                 : "TOL" <s>+ <nonquoted_string> <n>;
ptol                : "PTOL" <s>+ <nonquoted_string> <n>;
ntol                : "NTOL" <s>+ <nonquoted_string> <n>;
volts               : "VOLTS" <s>+ <string> <n>;
desc                : "DESC" <s>+ <string> <n>;
value               : ("VALUE"|"Value") <s>+ <wrapper_to_end> <n>;
partnumber          : "PartNumber" <s> <nonquoted_string> <n>;
device              : "DEVICE" <s>+ <part_name> <n> (<part>|<type>|<style>|<package>|<pindesc>|<pinfunct>|<pincount>|<value>|<tol>|<ntol>|<ptol>|<volts>|<desc>|<attribute>)* <n>*;
devices             : "$DEVICES" <n>* <device>* "$ENDDEVICES" <n>*;
node                : "NODE" <s>+ <component_name> <s> <pin_name> <n>*;
nailloc             : "NAILLOC" <s>+ <component_name> <s> <pin_name> <s> <tp_name> <s> <x_y_ref> <s> <tan> <s> <tin> <s> <probe> <s> <layer> <n>*;
signal              : "SIGNAL" <s>+ <sig_name> <n>* (<node>|<nailloc>|<attribute>)* <n>*;
signals             : "$SIGNALS" <n>* <signal>* "$ENDSIGNALS" <n>*;
track               : "TRACK" <s>+ <track_name> <s> <track_width> <n>*;
tracks              : "$TRACKS" <n>* <track>* "$ENDTRACKS" <n>*;
define              : "DEFINE" <s>+ <layer> <s> (<nonquoted_string>|<string>) <n>*;
layerset            : "LAYERSET" <s>+ <layer> <n> <layer_>*;
layer_              : "LAYER" <s>+ <layer> <n>*;
layers              : "$LAYERS" <n>* (<define>|<layerset>)* "$ENDLAYERS" <n>*;
track_              : "TRACK" <s>+ <track_name> <n>;
route               : "ROUTE" <s>+ <sig_name> <n> (<track_>|<layer_>|<line>|<arc>|<circle>|<rectangle>|<via>|<testpad>|<plane>|<text>|<attribute>)*;
nailloc_            : "NAILLOC" <s>+ <via_name> <s> <tp_name> <s> <x_y_ref> <s> <tan> <s> <tin> <probe> <s> <layer> <n>*;
via                 : "VIA" <s>+ <pad_name> <s> <x_y_ref> <s> <layer> <s> <drill_size> <s> <via_name> <n> (<nailloc_>|<attribute>)*;
testpad             : "TESTPAD" <s>+ <pad_name> <s> <x_y_ref> <s> <rot> <s> <mirror> <s> <testpad_name> <n>;
plane               : "PLANE" <s>+ <nonquoted_string> <n> (<line>|<arc>|<circle>|<rectangle>|<attribute>)*;
routes              : "$ROUTES" <n>* (<route>)* "$ENDROUTES" <n>*;
hole                : "HOLE" <s>+ <x_y_ref> <s> <drill_size> <n>;
fhole               : "FHOLE" <s>+ <x_y_ref> <s> <drill_size> <n>;
mechanical          : "MECHANICAL" <s>+ <part_name> <s>? <string>? <n> (<place>|<layer_>|<rotation>|<shape_>)*;
mech                : "$MECH" <n> (<hole>|<fhole>|<mechanical>|<attribute>|<artwork_>|<fid>)* "$ENDMECH" <n>*;
testpin             : "TESTPIN" <s>+ <tp_name> <s> <x_y_ref> <s> <sig_name> <s> <tan> <s> <tin> <s> <probe> <s> <layer> <n>*;
testpins            : "$TESTPINS" <n> (<testpin>|<text>|<attribute>)* "$ENDTESTPINS" <n>*;
powerpin            : "POWERPIN" <s>+ <tp_name> <s> <x_y_ref> <s> <sig_name> <s> <tan> <s> <tin> <s> <probe> <s> <layer> <n>*;
powerpins           : "$POWERPINS" <n> (<powerpin>|<text>|<attribute>)* "$ENDPOWERPINS" <n>*;
pseudo_signal       : "SIGNAL" <s>+ <sig_name> <s> <string> <n>;
pseudo_device       : "DEVICE" <s>+ <part_name> <s> <string> <n>;
pseudo_part         : "PART" <s>+ <part_name> <s> <string> <n>;
pseudo_shape        : "SHAPE" <s>+ <shape_name> <s> <string> <n>;
pseudo_component    : "COMPONENT" <s>+ <component_name> <s> <string> <n>;
pseudo_testpad      : "TESTPAD" <s>+ <pad_name> <s> <string> <n>;
pseudo_padstack     : "PADSTACK" <s>+ <pad_name> <s> <string> <n>;
pseudo_pin          : "PIN" <s>+ <pin_name> <s> <string> <n>;
pseudo_testpin      : "TESTPIN" <s>+ <tp_name> <s> <string> <n>;
pseudo_powerpin     : "POWERPIN" <s>+ <tp_name> <s> <string> <n>;
pseudo_via          : "VIA" <s>+ <via_name> <s> <string> <n>;
pseudos             : "$PSEUDOS" <n> (<pseudo_signal>|<pseudo_device>|<pseudo_part>|<pseudo_shape>|<pseudo_component>|<pseudo_testpad>|<pseudo_padstack>|<pseudo_pin>|<pseudo_testpin>|<pseudo_powerpin>|<pseudo_via>|<pseudo_testpad>)* "$ENDPSEUDOS" <n>*;
sig_change          : "SIGNAL" <s>+ <sig_name> <s> <sig_name> <n>;
dev_change          : "DEVICE" <s>+ <part_name> <s> <part_name> <n>;
change              : "CHANGE" <s>+ <string> <n> (<sig_change>|<dev_change>)*;
changes             : "$CHANGES" <n> <change>* "$ENDCHANGES";
gencad_file         : <header> (<board>|<pads>|<padstacks>|<artworks>|<shapes>|<devices>|<components>|<signals>|<tracks>|<layers>|<routes>|<mech>|<testpins>|<powerpins>|<pseudos>|<changes>)*;
)MultiLineString"; /*SKIP_LINE_IN_GRAMMAR_GENERATOR*/
