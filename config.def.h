/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;          /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;         /* snap pixel */
static const int showbar            = 1;          /* 0 means no bar */
static const int topbar             = 1;          /* 0 means bottom bar */
static const int usealtbar          = 0;          /* 1 means use non-dwm status bar */
static const char *altbarclass      = "";         /* Alternate bar class name */
static const char *alttrayname      = "";         /* Polybar tray instance name */
static const char *altbarcmd        = "";         /* Alternate bar launch command */
static const char *fonts[]          = { 
	"RobotoMono Nerd Font:style=Regular:size=11",
	"Noto Color Emoji:style=Regular:size=11",
	"Material Icons:size=10",
	"Font Awesome 5 Brands:style=Solid:size=11",
	"Font Awesome 5 Free:style=Regular:size=11",
	"Font Awesome 5 Free:style=Solid:size=11",
};
static const char dmenufont[]       = "FiraCode Nerd Font:size=11";
static const char startup[]         = "$HOME/.config/myscripts/startup.x11.sh";
static const char *colors[][3]      = {
	/*               fg         bg        border   */
	[SchemeNorm] = { "#D5C4A1", "#282828", "#282828"},
	[SchemeSel]  = { "#FBF1C7", "#3C3836", "#FFAF3E"},
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
#include "shiftview.c"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define FISHCMD(cmd) { .v = (const char*[]){ "/bin/fish", "-c", cmd, NULL } }
#define SCRIPT(name) "~/.config/myscripts/"name
#define FISH(cmd) { "/bin/fish", "-c", cmd, NULL }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { 
	"dmenu_run", 
	"-c", 
	"-l", 
	"14", 
	"-m",  dmenumon, 
	"-fn", dmenufont, 
	NULL 
};
static const char *termcmd[]  = { "kitty", NULL };
/* sound */
static const char *upvol[]      = { "pamixer", "-ui", "5", NULL };
static const char *downvol[]    = { "pamixer", "-ud", "5", NULL };
static const char *mutevol[]    = { "pamixer", "--toggle-mute", NULL };
static const char *pausetrack[] = { "playerctl", "play-pause", NULL };
static const char *prevtrack[]  = { "playerctl", "previous", NULL };
static const char *nexttrack[]  = { "playerctl", "next", NULL };
/* screenshot */
static const char *screenshot[] = { "bash", "-c", "~/.scripts/screenshot.sh", NULL };
static const char *sshot_area[] = { "bash", "-c", "~/.scripts/screenshot.sh region", NULL };
/* brightness */
static const char *brightup[]   = { "xbacklight", "+5", NULL };
static const char *brightdown[] = { "xbacklight", "-5", NULL };
/* scripts */
static const char *powermenu[]  = FISH(SCRIPT("powermenu.x11.rofi.fish"));
static const char *rofilauncher[] = FISH(SCRIPT("launcher.x11.rofi.fish"));
static const char *kblayout_menu[] = FISH(SCRIPT("kb-layouts.x11.rofi.fish"));

static Key keys[] = {
	/* modifier           key                     function        argument */
	{ MODKEY,             XK_o,                      spawn,          {.v = rofilauncher } },
	{ MODKEY|ShiftMask,   XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,             XK_b,                      togglebar,      {0} },
	{ MODKEY,             XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,             XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_j,                      pushdown,       {0} },
	{ MODKEY|ShiftMask,   XK_k,                      pushup,         {0} },
	{ MODKEY,             XK_i,                      incnmaster,     {.i = +1 } }, /* increment a master */
	{ MODKEY,             XK_d,                      incnmaster,     {.i = -1 } }, /* decrement a master */
	{ MODKEY,             XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_Return,                 zoom,           {0} }, /* make master */
	{ MODKEY,             XK_Tab,                    view,           {0} }, /* view last recently used tag on the same monitor */
	{ MODKEY,             XK_c,                      killclient,     {0} },
	{ MODKEY,             XK_t,                      setlayout,      {.v = &layouts[0]} }, /* TILE MODE */
	{ MODKEY,             XK_f,                      setlayout,      {.v = &layouts[1]} }, /* FLOAT MODE */
	{ MODKEY,             XK_m,                      setlayout,      {.v = &layouts[2]} }, /* MAXIMIZED MODE */
	{ MODKEY,             XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,   XK_space,                  togglefloating, {0} },
	{ MODKEY,             XK_0,                      view,           {.ui = ~0 } }, /* shows all main from a monitor */
	{ MODKEY|ShiftMask,   XK_0,                      tag,            {.ui = ~0 } }, /* sets current main as 'universal main' on all tags of a monitor, it set current main as another tag's main if different than XK_0, eg. XK_2 */
	{ MODKEY,             XK_comma,                  focusmon,       {.i = -1 } }, /* focus on LEFT monitor*/
	{ MODKEY,             XK_period,                 focusmon,       {.i = +1 } }, /* ^^ on the RIGHT */
	{ MODKEY|ShiftMask,   XK_comma,                  tagmon,         {.i = -1 } }, /* drag tag's main to the LEFT monitor*/
	{ MODKEY|ShiftMask,   XK_period,                 tagmon,         {.i = +1 } }, /* ^^ on the RIGHT */
	{ MODKEY,             XK_x,                      spawn,          {.v = powermenu } },
	TAGKEYS(              XK_1,                                      0)
	TAGKEYS(              XK_2,                                      1)
	TAGKEYS(              XK_3,                                      2)
	TAGKEYS(              XK_4,                                      3)
	TAGKEYS(              XK_5,                                      4)
	TAGKEYS(              XK_6,                                      5)
	TAGKEYS(              XK_7,                                      6)
	TAGKEYS(              XK_8,                                      7)
	TAGKEYS(              XK_9,                                      8)
	{ MODKEY|ShiftMask,   XK_x,                      quit,           {0} },
	{ MODKEY,             XK_minus,                  setgaps,        {.i = -5 } },
	{ MODKEY,             XK_equal,                  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,   XK_g,                      setgaps,        {.i = GAP_RESET } },
	{ MODKEY,             XK_g,                      setgaps,        {.i = GAP_TOGGLE} },
	{ 0,                  XF86XK_AudioMute,          spawn,          {.v = mutevol } },
	{ 0,                  XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },
	{ 0,                  XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },
	{ 0,                  XF86XK_AudioPlay,	         spawn,          {.v = pausetrack } },
	{ 0,                  XF86XK_AudioNext,    	     spawn,          {.v = nexttrack  } },
	{ 0,                  XF86XK_AudioPrev,    	     spawn,          {.v = prevtrack  } },
	{ MODKEY|AltMask,     XK_j,                      shiftview,      {.i = -1 } },
	{ MODKEY|AltMask,     XK_k,                      shiftview,      {.i = +1 } },
	{ AltMask,            XK_m,                      focusmaster,    {0} },
	{ 0,                  XK_Print,                  spawn,          {.v = screenshot } },
	{ ControlMask,        XK_Print,                  spawn,          {.v = sshot_area} },
	{ 0,                  XF86XK_MonBrightnessUp,    spawn,          {.v = brightup } },
	{ 0,                  XF86XK_MonBrightnessDown,  spawn,          {.v = brightdown } },
	{ MODKEY|ControlMask, XK_l,                      spawn,          {.v = kblayout_menu} },
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

