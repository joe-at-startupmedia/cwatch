CWatch
======

**Cwatch** is a program that examines a logfile for interesting patterns and does various things with those patterns. It’s a clone of the the [swatch](http://www.oit.ucsb.edu/~eta/swatch/) program, except that it’s written in **yacc**, **lex**, and **C** (using the [pcre](http://www.pcre.org) library). I wrote it because the latest versions of swatch require many additional perl modules from [CPAN](http://www.cpan.org) and I wanted to do spam monitoring without having to be forced into upgrading to the most recent version of perl to do it.

I used **cwatch** for a year or so on pell to help me deal with spam. I modified [`sendmail`](http://www.sendmail.org) so that it denies access from sites that were listed in the (_dead and gone_) [ORDB](http://www.ordb.org), that don’t have a functional reverse DNS, or which came from sites that sent me too much spam and got bunged into my `tcp wrappers` deny list. Every time `sendmail` refused a connection, it would `syslog` it and then **cwatch** could pick it up and fire off a program to check and see if that connection was coming from a new open relay. It worked pretty well up until the point where the spammers started using viruses to take over machines that they could use as spam zombies.

**Cwatch** is not a perfect clone of swatch. There are a few differences an omissions resulting from the different implementation languages and things that aren’t documented in the swatch manpage:

*   **`watchfor`** and **`ignore`** take a single regex.
*   **`exec`** and **`pipe`**, take a single quoted string as the commandline to run instead of all the text up ‘til the **`when=`** or **`keep_open`** option (or end of line?)
*   The modes for **`echo`** aren’t used.
*   I can’t figure out just how the **`use`** option for **`throttle`** works, so my version of it works the way I think it should work:
    
    *   **`use=regex`** Throttles the action until the time runs out or until any _other_ pattern is matched.
        
    *   **`use=message`** Throttles the action until the time runs out or until the _throttled_ pattern matches different text.
        
*   **`Throttle`** also doesn’t do clip regions, because clip regions are easily defeated by applications reporting their pid in syslog. To replace that functionality, I have **`use=message`** report the matched pattern and **`use=regex`** report the regex when the throttle expires.
    

**Cwatch** uses my [auto-configuration](https://www.pell.portland.or.us/~orc/Code/configure/) tools for building on various platforms. To install cwatch, follow the instructions in the INSTALL file.

Source Code
-----------

*   [v0.97](cwatch-0.97.tar.gz) fixes no bugs, but tweaks the source so it can be built with gnuware. `lex` and `yacc` turn out, not surprisingly, to work differently from the gnuware equivalents, and a grammar that `yacc` builds without fuss blows up in gnuland. The grammar has now been tweaked to build with gnuware.
    
*   [v0.96](cwatch-0.96.tar.gz) fixes a (recently introduced?) bug in signal handling and adds some cosmetics – when a **`throttle`** expires, the message says how many times the pattern was matched (_including_ the first match) and how much time passed between the first and last pattern match.
    
*   Coming quickly on the tail of 0.81 comes [v0.9](cwatch-0.9.tar.gz), which implements, for better or worse, the **`restart-time`** option and the **`write`** command. At this point, cwatch appears to implement everything that swatch does except for colored **`echo`**.
    
*   [v0.81](cwatch-0.81.tar.gz) is a hurried replacement for 0.75, because that release had the embarrassing bug (on linux, at the very least) that when an alarm fires and is serviced, the alarm handler resets back to the default. This means that the second throttle causes a reset, which is not exactly what I intended it to do.


### Original Readme file

_"This is my attempt at doing a swatchalike in C; it implements, fuzzily,
about 95% of what the perl version does (at least as far as I can
interpret the documentation & the perl source of the original._

_I am not a system administrator anymore (I administer a few machines
scattered around, but they're the standard Linux style of being boxes
without users, just service providers) so I don't use this code much
myself.  But I think it's still useful on the occasional time I need to
have some sort of log sweeper running."_
