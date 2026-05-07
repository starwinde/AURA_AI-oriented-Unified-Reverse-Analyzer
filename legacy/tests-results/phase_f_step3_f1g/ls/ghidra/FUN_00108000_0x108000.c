
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00108000(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined8 uVar3;
  char *pcVar4;
  undefined8 uVar5;
  undefined **ppuVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined *local_b8;
  undefined *puStack_b0;
  undefined *local_a8 [4];
  undefined *puStack_88;
  undefined *puStack_80;
  undefined *local_78;
  undefined *puStack_70;
  undefined *puStack_68;
  undefined *puStack_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  
  uVar5 = DAT_00140ed8;
  local_48 = *(undefined8 *)PTR___stack_chk_guard_0013ffd0;
  if (param_1 != 0) {
    uVar7 = *(undefined8 *)PTR_stderr_0013ffa0;
    uVar3 = dcgettext(0,"Try \'%s --help\' for more information.\n",5);
    __fprintf_chk(uVar7,2,uVar3,uVar5);
    goto LAB_00108074;
  }
  uVar3 = dcgettext(0,"Usage: %s [OPTION]... [FILE]...\n",5,0);
  puVar1 = PTR_stdout_0013ffc0;
  __printf_chk(2,uVar3,uVar5);
  pcVar4 = (char *)dcgettext(0,
                             "List information about the FILEs (the current directory by default).\nSort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nMandatory arguments to long options are mandatory for short options too.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -a, --all                  do not ignore entries starting with .\n  -A, --almost-all           do not list implied . and ..\n      --author               with -l, print the author of each file\n  -b, --escape               print C-style escapes for nongraphic characters\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --block-size=SIZE      with -l, scale sizes by SIZE when printing them;\n                             e.g., \'--block-size=M\'; see SIZE format below\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -B, --ignore-backups       do not list implied entries ending with ~\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -c                         with -lt: sort by, and show, ctime (time of last\n                             change of file status information);\n                             with -l: show ctime and sort by name;\n                             otherwise: sort by ctime, newest first\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -C                         list entries by columns\n      --color[=WHEN]         color the output WHEN; more info below\n  -d, --directory            list directories themselves, not their contents\n  -D, --dired                generate output designed for Emacs\' dired mode\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -f                         list all entries in directory order\n  -F, --classify[=WHEN]      append indicator (one of */=>@|) to entries WHEN\n      --file-type            likewise, except do not append \'*\'\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --format=WORD          across -x, commas -m, horizontal -x, long -l,\n                             single-column -1, verbose -l, vertical -C\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"      --full-time            like -l --time-style=full-iso\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"  -g                         like -l, but do not list owner\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --group-directories-first\n                             group directories before files;\n                             can be augmented with a --sort option, but any\n                             use of --sort=none (-U) disables grouping\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -G, --no-group             in a long listing, don\'t print group names\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -h, --human-readable       with -l and -s, print sizes like 1K 234M 2G etc.\n      --si                   likewise, but use powers of 1000 not 1024\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -H, --dereference-command-line\n                             follow symbolic links listed on the command line\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --dereference-command-line-symlink-to-dir\n                             follow each command line symbolic link\n                             that points to a directory\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --hide=PATTERN         do not list implied entries matching shell PATTERN\n                             (overridden by -a or -A)\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"      --hyperlink[=WHEN]     hyperlink file names WHEN\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --indicator-style=WORD\n                             append indicator with style WORD to entry names:\n                             none (default), slash (-p),\n                             file-type (--file-type), classify (-F)\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -i, --inode                print the index number of each file\n  -I, --ignore=PATTERN       do not list implied entries matching shell PATTERN\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -k, --kibibytes            default to 1024-byte blocks for file system usage;\n                             used only with -s and per directory totals\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"  -l                         use a long listing format\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -L, --dereference          when showing file information for a symbolic\n                             link, show information for the file the link\n                             references rather than for the link itself\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -m                         fill width with a comma separated list of entries\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -n, --numeric-uid-gid      like -l, but list numeric user and group IDs\n  -N, --literal              print entry names without quoting\n  -o                         like -l, but do not list group information\n  -p, --indicator-style=slash\n                             append / indicator to directories\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -q, --hide-control-chars   print ? instead of nongraphic characters\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --show-control-chars   show nongraphic characters as-is (the default,\n                             unless program is \'ls\' and output is a terminal)\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"  -Q, --quote-name           enclose entry names in double quotes\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --quoting-style=WORD   use quoting style WORD for entry names:\n                             literal, locale, shell, shell-always,\n                             shell-escape, shell-escape-always, c, escape\n                             (overrides QUOTING_STYLE environment variable)\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -r, --reverse              reverse order while sorting\n  -R, --recursive            list subdirectories recursively\n  -s, --size                 print the allocated size of each file, in blocks\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"  -S                         sort by file size, largest first\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --sort=WORD            sort by WORD instead of name: none (-U), size (-S),\n                             time (-t), version (-v), extension (-X), width\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --time=WORD            select which timestamp used to display or sort;\n                               access time (-u): atime, access, use;\n                               metadata change time (-c): ctime, status;\n                               modified time (default): mtime, modification;\n                               birth time: birth, creation;\n                             with -l, WORD determines which time to show;\n                             with --sort=time, sort by WORD (newest first)\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "      --time-style=TIME_STYLE\n                             time/date format with -l; see TIME_STYLE below\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -t                         sort by time, newest first; see --time\n  -T, --tabsize=COLS         assume tab stops at each COLS instead of 8\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -u                         with -lt: sort by, and show, access time;\n                             with -l: show access time and sort by name;\n                             otherwise: sort by access time, newest first\n\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -U                         do not sort; list entries in directory order\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -v                         natural sort of (version) numbers within text\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "  -w, --width=COLS           set output width to COLS.  0 means no limit\n  -x                         list entries by lines instead of by columns\n  -X                         sort alphabetically by entry extension\n  -Z, --context              print any security context of each file\n      --zero                 end each output line with NUL, not newline\n  -1                         list one file per line\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"      --help        display this help and exit\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,"      --version     output version information and exit\n",5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nThe SIZE argument is an integer and optional unit (example: 10K is 10*1024).\nUnits are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\nBinary prefixes can be used, too: KiB=K, MiB=M, and so on.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nThe TIME_STYLE argument can be full-iso, long-iso, iso, locale, or +FORMAT.\nFORMAT is interpreted like in date(1).  If FORMAT is FORMAT1<newline>FORMAT2,\nthen FORMAT1 applies to non-recent files and FORMAT2 to recent files.\nTIME_STYLE prefixed with \'posix-\' takes effect only outside the POSIX locale.\nAlso the TIME_STYLE environment variable sets the default style to use.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nThe WHEN argument defaults to \'always\' and can also be \'auto\' or \'never\'.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nUsing color to distinguish file types is disabled both by default and\nwith --color=never.  With --color=auto, ls emits color codes only when\nstandard output is connected to a terminal.  The LS_COLORS environment\nvariable can change the settings.  Use the dircolors(1) command to set it.\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  pcVar4 = (char *)dcgettext(0,
                             "\nExit status:\n 0  if OK,\n 1  if minor problems (e.g., cannot access subdirectory),\n 2  if serious trouble (e.g., cannot access command-line argument).\n"
                             ,5);
  fputs_unlocked(pcVar4,*(FILE **)puVar1);
  ppuVar6 = &local_b8;
  pcVar4 = "[";
  puStack_b0 = PTR_s_test_invocation_00140018;
  local_b8 = PTR_DAT_00140010;
  local_a8[1] = PTR_s_Multi_call_invocation_00140028;
  local_a8[0] = PTR_s_coreutils_00140020;
  local_a8[3] = PTR_s_sha2_utilities_00140038;
  local_a8[2] = PTR_s_sha224sum_00140030;
  puStack_80 = PTR_s_sha2_utilities_00140048;
  puStack_88 = PTR_s_sha256sum_00140040;
  puStack_70 = PTR_s_sha2_utilities_00140058;
  local_78 = PTR_s_sha384sum_00140050;
  puStack_60 = PTR_s_sha2_utilities_00140068;
  puStack_68 = PTR_DAT_00140060;
  uStack_50 = uRam0000000000140078;
  local_58 = _DAT_00140070;
  do {
    if (((*pcVar4 == 'l') && (pcVar4[1] == 's')) && (pcVar4[2] == '\0')) break;
    ppuVar6 = ppuVar6 + 2;
    pcVar4 = *ppuVar6;
  } while (pcVar4 != (char *)0x0);
  puVar8 = ppuVar6[1];
  if (puVar8 == (undefined *)0x0) {
    uVar5 = dcgettext(0,"\n%s online help: <%s>\n",5);
    __printf_chk(2,uVar5,"GNU coreutils","https://www.gnu.org/software/coreutils/");
    pcVar4 = setlocale(5,(char *)0x0);
    if (pcVar4 != (char *)0x0) {
      puVar8 = &DAT_00119c00;
      goto LAB_00108660;
    }
    puVar8 = &DAT_00119c00;
    uVar5 = dcgettext(0,"Full documentation <%s%s>\n",5);
    __printf_chk(2,uVar5,"https://www.gnu.org/software/coreutils/",&DAT_00119c00);
    uVar5 = dcgettext(0,"or available locally via: info \'(coreutils) %s%s\'\n",5);
    pcVar4 = " invocation";
  }
  else {
    uVar5 = dcgettext(0,"\n%s online help: <%s>\n",5);
    __printf_chk(2,uVar5,"GNU coreutils","https://www.gnu.org/software/coreutils/");
    pcVar4 = setlocale(5,(char *)0x0);
    if (pcVar4 != (char *)0x0) {
LAB_00108660:
      iVar2 = strncmp(pcVar4,"en_",3);
      if (iVar2 != 0) {
        pcVar4 = (char *)dcgettext(0,
                                   "Report any translation bugs to <https://translationproject.org/team/>\n"
                                   ,5);
        fputs_unlocked(pcVar4,*(FILE **)puVar1);
      }
    }
    uVar5 = dcgettext(0,"Full documentation <%s%s>\n",5);
    __printf_chk(2,uVar5,"https://www.gnu.org/software/coreutils/",&DAT_00119c00);
    uVar5 = dcgettext(0,"or available locally via: info \'(coreutils) %s%s\'\n",5);
    pcVar4 = "";
    if (puVar8 == &DAT_00119c00) {
      pcVar4 = " invocation";
    }
  }
  __printf_chk(2,uVar5,puVar8,pcVar4);
LAB_00108074:
                    /* WARNING: Subroutine does not return */
  exit(param_1);
}

