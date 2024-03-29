/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;       /* vert inner gap between windows */
static const unsigned int gappoh    = 7;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;     /* horizontal padding of bar */
static const unsigned int baralpha  = 200;
static const unsigned int borderalpha = OPAQUE;
static const char *fonts[]          = { "Ubuntu:weight=bold:size=8:antialias=true:hinting=true",
                                        "Font Awesome 6 Pro Solid:pixelsize=10",
                                        "Font Awesome 6 Brands:pixelsize=10"};
static const char dmenufont[]       = "monospace:size=9";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#111111";
static const char col_gray3[]       = "#777777";
static const char col_gray4[]       = "#8e8e8e";
static const char bar_sel_fg[]      = "#bbbbbb";
static const char bar_sel_bg[]      = "#000000";
static const char col_cyan[]        = "#005577";
static const char window_border[]   = "#555555";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { bar_sel_fg, bar_sel_bg,  window_border  },
};

static const unsigned int alphas[][3]      = {
/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
 
/* tagging */
static const char *tags[] = { "","","","","","","","","" };
static const char *tagsalt[] = { "home", "term", "web", "code", "file", "read", "play", "notes", "*" };
static const int momentaryalttags = 0; /* 1 means /alttags will show only when key is held down*/


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
        { "qBittorrent",	NULL,       NULL,       1 << 8,			0,           -1 },
        { "Firefox",		NULL,       NULL,       1 << 2,			0,           -1 },
        { "Chromium",	NULL,       NULL,       1 << 2,			0,           -1 },
        { "qutebrowser",	NULL,       NULL,       1 << 2,			0,           -1 },
        { "Zathura",		NULL,       NULL,       1 << 5,			0,           -1 },
        { "Subl",	        NULL,       NULL,       1 << 3,			0,           -1 },
        { "Code",	        NULL,       NULL,       1 << 3,			0,           -1 },
        { "LF",	            NULL,       NULL,       1 << 4,			0,           -1 },
        { "newsboat",       NULL,       NULL,       1 << 5,			0,           -1 },
        { "ncmpcpp",	    NULL,       NULL,       1 << 6,			0,           -1 },
        { "term1n4l",	    NULL,       NULL,       1 << 1,			0,           -1 },
        { "h0m3t3rm",	    NULL,       NULL,       1 << 0,			0,           -1 },
        { "mpv",	    NULL,       NULL,       1 << 6,			0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "===",      bstackhoriz },
	{ "H[]",      deck },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

static const MonitorRule monrules[] = {
	/* monitor  tag  layout  mfact  nmaster  showbar  topbar */
	{   -1,      1,  1,      -1,    -1,      -1,      -1     }, 
	{   -1,      2,  7,      -1,    -1,      -1,      -1     }, 
	{   -1,      3,  0,      -1,    -1,      -1,      -1     }, 
	{   -1,      4,  0,      -1,    -1,      -1,      -1     }, 
	{   -1,      5,  0,      -1,    -1,      -1,      -1     }, 
	{   -1,      6,  7,      -1,    -1,      -1,      -1     }, 
	{   -1,      7,  0,      -1,    -1,      -1,      -1     }, 
	{   -1,      8,  0,      -1,    -1,      -1,      -1     }, 
	{   -1,      9,  0,      -1,    -1,      -1,      -1     }, 
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st","-c term1n4l", NULL };
static const char *termhomecmd[]  = { "st","-c h0m3t3rm", NULL };

static const Key keys[] = {
	/* media keys */
    {0,                 XF86XK_AudioRaiseVolume,        spawn,   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +10%") },
    {0,                 XF86XK_AudioLowerVolume,        spawn,   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -10%") },
    {0,                 XF86XK_AudioMute,               spawn,   SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
    {0,                 XF86XK_AudioMicMute,            spawn,   SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    {0,                 XF86XK_AudioPrev,               spawn,   SHCMD("mpc prev") },
    {0,                 XF86XK_AudioPlay,               spawn,   SHCMD("mpc toggle") },
    {0,                 XF86XK_AudioNext,               spawn,   SHCMD("mpc next") },
     /*ThinkVantage Key*/
    {0,                 XF86XK_Launch1,                 spawn,   SHCMD("xset dpms force off") },
     /* brightness control */
    {0,                 XF86XK_MonBrightnessDown,		spawn,  SHCMD("light -U 10") },
    {0,                 XF86XK_MonBrightnessUp,			spawn,  SHCMD("light -A 10") },
    {0,                 XF86XK_ScreenSaver,			    spawn,  SHCMD("slock") },
     /* screenshot: pacman -S scrot */
    {0,                 XK_Print,                       spawn,  SHCMD("scrot scrot_%Y-%m-%d-%T_$wx$h.png") },
     /* dmenu scripts */
    { MODKEY|ShiftMask,             XK_e,      spawn,           SHCMD("~/.bin/pmenu") },
      /* ncmpcpp */
    { MODKEY|ShiftMask,             XK_m,      spawn,           SHCMD("st -c ncmpcpp -e ncmpcpp") },
      /*lf file manager*/
    { MODKEY|ShiftMask,             XK_l,      spawn,           SHCMD("st -c LF -e lfrun") },
      /* nvim shortcut */
    { MODKEY|ShiftMask,             XK_v,      spawn,           SHCMD("st -c vim -e nvim") },
      /* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("firefox") }, 
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Menu, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termhomecmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              0,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              0,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    0,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    0,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  0,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  0,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_g,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    0,      defaultgaps,    {0} },
	{ MODKEY,                       0,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       0,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           0,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           0,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              0,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              0,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             0,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             0,      incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY,                       XK_s, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_s, scratchpad_hide, {0} },
	{ MODKEY,                       XK_a,scratchpad_remove,{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

