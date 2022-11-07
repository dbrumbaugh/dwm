/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */

static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "FiraCode Nerd Font:style=medium:antialias=true:pixelsize=16";
static char dmenufont[]       = "FiraCode Nerd Font:style=medium:antialias=true:pixelsize=16";
static char statusfont[]      = "FiraCode Nerd Font:style=medium:antialias=true:pixelsize=16";

static const char *fonts[]          = { font, statusfont };
static const int statusfontindex = 1;

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };

/* scratchpads setup */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"kitty", "--name", "spcalc", "-e", "calc", NULL };
const char *spcmd2[] = {"kitty", "--name", "spterm",  NULL };
const char *spcmd3[] = {"kitty", "--name", "spnvim", "-e", "nvim", NULL };
const char *spcmd4[] = {"kitty", "--name", "spmixer", "-e", "cmixer", NULL};
const char *spcmd5[] = {"kitty", "--name", "spmusic", "-e", "ncmpcpp", NULL};
const char *spcmd6[] = {"kitty", "--name", "sptop", "-e", "htop", NULL};

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spcalc",    spcmd1},
	{"spterm",    spcmd2},
	{"spnvim",    spcmd3},
    {"spmixer",   spcmd4},
    {"spmusic", spcmd5},
    {"sptop", spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  		title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Kitty",      NULL,     		NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      "kitty",     		NULL,		   	0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     		"Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,     		"zoom",                0,  1,          0,           0,        -1 }, /* xev */
	{ NULL,		 "spcalc",		NULL,			SPTAG(0),  1,		   1,           0,        -1 },
	{ NULL,		 "spterm",		NULL,			SPTAG(1),  1,		   1,           0,        -1 },
	{ NULL,		 "spnvim",		NULL,			SPTAG(2),  1,		   1,           0,        -1 },
	{ NULL,		 "spmixer",		NULL,			SPTAG(3),  1,		   1,           0,        -1 },
	{ NULL,		 "spmusic",		NULL,			SPTAG(4),  1,		   1,           0,        -1 },
	{ NULL,		 "sptop",		NULL,			SPTAG(5),  1,		   1,           0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "kitty", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		//{ "font",               STRING,  &font },
		//{ "dmenufont",          STRING,  &dmenufont },

		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
        { "color0",             STRING,  &termcol0},
        { "color1",             STRING,  &termcol1},
        { "color2",             STRING,  &termcol2},
        { "color3",             STRING,  &termcol3},
        { "color4",             STRING,  &termcol4},
        { "color5",             STRING,  &termcol5},
        { "color6",             STRING,  &termcol6},
        { "color7",             STRING,  &termcol7},
        { "color8",             STRING,  &termcol8},
        { "color9",             STRING,  &termcol9},
        { "color10",             STRING,  &termcol10},
        { "color11",             STRING,  &termcol11},
        { "color12",             STRING,  &termcol12},
        { "color13",             STRING,  &termcol13},
        { "color14",             STRING,  &termcol14},
        { "color15",             STRING,  &termcol15},
};

static const char *vpn_launch[] = { "vpn-connect", "ARGUMENTS", NULL};

#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,    		            XK_Return, spawn,          {.v = termcmd } },

	{ 0,    		                XK_Print,  spawn,          SHCMD("maim -sl -c .27,.5214,.5333,.8 ~/pictures/screenshots/$(date +%s).png") },
	{ 0|ShiftMask,                  XK_Print,  spawn,          SHCMD("maim ~/pictures/screenshots/$(date +%s).png") },

	{ MODKEY,    		            XK_Home, spawn,            {.v = vpn_launch} },
	//{ MODKEY,    		            XK_Prior, spawn,          {.v = termcmd } },
	//{ MODKEY,    		            XK_Next, spawn,          {.v = termcmd } },
	//{ MODKEY,    		            XK_End, spawn,          {.v = termcmd } },

	//{ MODKEY|ShiftMask,           XK_Home, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,           XK_Prior, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,           XK_Next, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,           XK_End, spawn,          SHCMD("poweroff")},


	//{ MODKEY,    		            XK_Left, spawn,          {.v = termcmd } },
	//{ MODKEY,    		            XK_Right, spawn,          {.v = termcmd } },
	//{ MODKEY,    		            XK_Up, spawn,          {.v = termcmd } },
	//{ MODKEY,    		            XK_Down, spawn,          {.v = termcmd } },

	//{ MODKEY|ShiftMask,           XK_Left, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,           XK_Right, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,           XK_Up, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,           XK_Down, spawn,          {.v = termcmd } },


    /* 1 - 0 */
	//{ MODKEY,                     XK_grave,      view,           {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,           view,           {.ui = ~0 } },
	{ MODKEY,                       XK_equal,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,       incnmaster,     {.i = -1 } },
	//{ MODKEY,                     XK_BackSpace,   <stuff>,        {} },

    /* Shift with 1 - 0 */
	//{ MODKEY|ShiftMask,           XK_grave,       <stuff>,           {} },
	{ MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
	//{ MODKEY|ShiftMask,           XK_equal,       <stuff>,     {} },
	//{ MODKEY|ShiftMask,           XK_minus,       <stuff>,     {} },
	//{ MODKEY|ShiftMask,           XK_BackSpace,   <stuff>,     {} },


    /* Q - P */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_w,      togglebar,      {0}  },
    { MODKEY,                       XK_e,      spawn,          SHCMD("launch-webcam")  },
    { MODKEY,                       XK_r,      spawn,          SHCMD("screencast")  },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[7]} },
    { MODKEY,                       XK_p,      spawn,          SHCMD("toggle-picom")  },
    //{ MODKEY,                     XK_bracketleft,     <stuff>,          {} },
    //{ MODKEY,                     XK_bracketright,    <stuff>,          {} },
    //{ MODKEY,                     XK_backslash,       <stuff>,          {} },

    /* Shift with Q - P */
    //{ MODKEY|ShiftMask,           XK_Tab,    <stuff>,      {} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    //{ MODKEY|ShiftMask,           XK_w,      <stuff>,      {} },
    //{ MODKEY|ShiftMask,           XK_e,      <stuff>       {} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
	//{ MODKEY|ShiftMask,           XK_t,      <stuff>,      {} },
	//{ MODKEY|ShiftMask,           XK_y,      <stuff>,      {} },
	//{ MODKEY|ShiftMask,           XK_u,      <stuff>,      {} },
	//{ MODKEY|ShiftMask,           XK_i,      <stuff>,      {} },
	//{ MODKEY|ShiftMask,           XK_o,      <stuff>,      {} },
    //{ MODKEY|ShiftMask,           XK_p,      <stuff>,      {} },
    //{ MODKEY|ShiftMask,           XK_bracketleft,   <stuff>,     {} },
    //{ MODKEY|ShiftMask,           XK_bracketright,  <stuff>,     {} },
    //{ MODKEY|ShiftMask,           XK_backslash,     <stuff>,     {} },
    

    /* A - L */
    { MODKEY,                       XK_a,      spawn,          SHCMD("sndioctl output.level=-.05")  },
    { MODKEY,                       XK_s,      spawn,          SHCMD("sndioctl output.mute=!")  },
    { MODKEY,                       XK_d,      spawn,          SHCMD("sndioctl output.level=+.05")  },
    //{ MODKEY,                     XK_f,      <stuff>         {} },
    //{ MODKEY,                     XK_g,      <stuff>         {} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_semicolon,     spawn,   SHCMD("passmenu") },
	//{ MODKEY,                     XK_apostrophe,     <stuff>,       {} },

    /* Shift with A - L */
    { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("sndioctl input.level=-.05")  },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("sndioctl input.mute=!")  },
    { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("sndioctl input.level=+.05")  },
    //{ MODKEY|ShiftMask,           XK_f,      <stuff>         {} },
    //{ MODKEY|ShiftMask,           XK_g,      <stuff>         {} },
    //{ MODKEY|ShiftMask,           XK_h,      <stuff>         {} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    //{ MODKEY|ShiftMask,           XK_l,      <stuff>         {} },
	//{ MODKEY|ShiftMask,           XK_semicolon,      <stuff>,       {} },
	//{ MODKEY|ShiftMask,           XK_apostrophe,     <stuff>,       {} },


    /* Z - M */
    { MODKEY,                       XK_z,      spawn,          SHCMD("mpc prev")  },
    { MODKEY,                       XK_x,      spawn,          SHCMD("mpc toggle")  },
    { MODKEY,                       XK_c,      spawn,          SHCMD("mpc next")  },
    { MODKEY,                       XK_v,      incrgaps,       {.i = +3}  },
    { MODKEY,                       XK_b,      incrgaps,       {.i = -3}  },
    { MODKEY,                       XK_n,      defaultgaps,    {0}  },
    { MODKEY,                       XK_m,      togglegaps,     {0}  },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_slash,      spawn,          {.v = dmenucmd } },

    /* Shift with Z - M */
    //{ MODKEY|ShiftMask,           XK_z,      spawn,          SHCMD("mpc prev")  },
    //{ MODKEY|ShiftMask,           XK_x,      spawn,          SHCMD("mpc toggle")  },
    //{ MODKEY|ShiftMask,           XK_c,      spawn,          SHCMD("mpc next")  },
    //{ MODKEY|ShiftMask,           XK_v,      spawn,       SHCMD("vpn-connect")  },
    //{ MODKEY|ShiftMask,           XK_b,      incrgaps,       {.i = -3}  },
    //{ MODKEY|ShiftMask,           XK_n,      defaultgaps,    {0}  },
    //{ MODKEY|ShiftMask,           XK_m,      togglegaps,     {0}  },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	//{ MODKEY|ShiftMask,           XK_slash, focusmon,       {.i = +1 } },


    /* Function Keys */
    { MODKEY,                       XK_Escape, spawn,           SHCMD("lock")},
    { MODKEY,                       XK_F1,     spawn,           SHCMD("qutebrowser")},
    { MODKEY,                       XK_F2,     spawn,           SHCMD("kitty neomutt")},
    { MODKEY,                       XK_F3,     spawn,           SHCMD("pkill newsboat; kitty newsboat -u /home/douglas/.local/share/feeds -c /home/douglas/.cache/newsboat/cache -C /home/douglas/.config/newsboat/config")},
    { MODKEY,                       XK_F4,     spawn,           SHCMD("kitty khal interactive")},
    { MODKEY,                       XK_F5,     spawn,           SHCMD("kitty weechat")},
    { MODKEY,                       XK_F6,     spawn,           SHCMD("")},
	{ MODKEY,            			XK_F7,     togglescratch,  {.ui = 5 } },
	{ MODKEY,            			XK_F8,     togglescratch,  {.ui = 4 } },
	{ MODKEY,            			XK_F9,     togglescratch,  {.ui = 3 } },
	{ MODKEY,            			XK_F10,    togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_F11,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,            			XK_F12,	   togglescratch,  {.ui = 1 } },
	//{ MODKEY,            			XK_Delete,	   togglescratch,  {.ui = 1 } },

    /* Shift with Function Keys */
    { MODKEY|ShiftMask,             XK_Escape, spawn,           SHCMD("toggle-lock")},
    //{ MODKEY|ShiftMask,                       XK_F1,     spawn,           SHCMD("qutebrowser")},
    //{ MODKEY|ShiftMask,                       XK_F2,     spawn,           SHCMD("kitty neomutt")},
    //{ MODKEY|ShiftMask,                       XK_F3,     spawn,           SHCMD("kitty newsboat -u /home/douglas/.local/share/feeds -c /home/douglas/.cache/newsboat/cache -C /home/douglas/.config/newsboat/config")},
    //{ MODKEY|ShiftMask,                       XK_F4,     spawn,           SHCMD("kitty khal interactive")},
    //{ MODKEY|ShiftMask,                       XK_F5,     spawn,           SHCMD("kitty weechat")},
    //{ MODKEY|ShiftMask,                       XK_F6,     spawn,           SHCMD("")},
	//{ MODKEY|ShiftMask,            			XK_F7,     togglescratch,  {.ui = 5 } },
	//{ MODKEY|ShiftMask,            			XK_F8,     togglescratch,  {.ui = 4 } },
	//{ MODKEY|ShiftMask,            			XK_F9,     togglescratch,  {.ui = 3 } },
	//{ MODKEY|ShiftMask,            			XK_F10,    togglescratch,  {.ui = 0 } },
	//{ MODKEY|ShiftMask,            			XK_F11,	   togglescratch,  {.ui = 2 } },
	//{ MODKEY|ShiftMask,            			XK_F12,	   togglescratch,  {.ui = 1 } },
	//{ MODKEY|ShiftMask,            			XK_Delete,	   togglescratch,  {.ui = 1 } },


    /* XF86 Media Keybindings */
    /*
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("kitty -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("kitty -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("systemctl suspend") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("kitty") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("kitty -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("kitty -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("kitty -e lf /") },
	 { 0, XF86XK_Battery,		spawn,		SHCMD("") }, 
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 5") },
    */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
#ifndef __OpenBSD__
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        view,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
