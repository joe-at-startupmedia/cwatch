/* prototypes for all */

/* cwatch.c */
extern void statement(int what);
extern void action(int order);
extern int re(char *pat);
extern void attrib(int attrib);
extern void fg(int color);
extern void bg(int color);
extern void nrbell(int num);
extern void keep_open(void);
extern void address(char *mailto);
extern void delay(int hr, int min, int sec);
extern void use(int flag);
extern void subject(char *pat);
extern void cmdline(char *command);
extern int day(unsigned int first, unsigned int last);
extern int hour(unsigned int first, unsigned int last);
extern struct pattern *compile(void);
