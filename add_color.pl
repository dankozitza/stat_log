#!/usr/bin/perl

my %colors = (
   black          => '\x1b[30m&\x1b[0m',
   white          => '\x1b[37m&\x1b[0m',
   cyan           => '\x1b[36m&\x1b[0m',
   green          => '\x1b[32m&\x1b[0m',
   red            => '\x1b[31m&\x1b[0m',
   yellow         => '\x1b[33m&\x1b[0m',
   magenta        => '\x1b[35m&\x1b[0m',
   blue           => '\x1b[34m&\x1b[0m',
   cyan_bg        => '\x1b[46m&\x1b[0m',
   blue_bg        => '\x1b[44m&\x1b[0m',
   purple_bg      => '\x1b[45m&\x1b[0m',
   green_bg       => '\x1b[42m&\x1b[0m',
   yellow_bg      => '\x1b[43m&\x1b[0m',
   red_bg         => '\x1b[41m&\x1b[0m',
   white_bg       => '\x1b[47m&\x1b[0m',
   bold           => '\x1b[1m&\x1b[0m',

);

#my %tags = (
#   TE_Assertion_Mgr => $colors{cyan},
##   'ASID='          => $colors{purple_bg},
#   PASS             => $colors{green_bg},
#   '=PASS'          => $colors{blue},
#   DEFINE           => $colors{purple_bg},
#   '=DEFINE'        => $colors{cyan},
#   FAIL             => $colors{red_bg},
#   ERROR            => $colors{bold_red},
#   TE_Rpc           => $colors{yellow},
#   TE_Status_Mgr    => $colors{magenta},
#   'NEW PROCESS'    => $colors{red},
#   ' NEW PROCESS'   => $colors{white_bg},
#   'TE_Test_Mgr'    => $colors{blue},
#   ' TE_Test_Mgr'   => $colors{white_bg},
#);

my %modifications = (
   cyan      => [
      "xfs_crawl",
   ],
   red => [
      "FAIL",
      "fail message",
   ],
   white => [
      "FATAL",
   ],
   red_bg => [
      "FATAL",
   ],
   bold => [
      "FATAL",
   ],
   green => [
      "PASS",
      "pass message",
   ],
#   blue      => ["PASS"],
#   yellow    => ["TE_Rpc"],
#   white     => [
#      "FAIL",
#      "ERROR",
#      "ErrMsg:",
#   ],
#   red_bg    => [
#      "FAIL",
#      "ERROR",
#      "ErrMsg:",
#   ],
#   green_bg  => ["PASS"],
#   purple_bg => ["DEFINE"],
#   yellow_bg   => [
#      "NEW PROCESS",
#      "BEGIN TEST OUTPUT",
#      "END TEST OUTPUT",
#      "RETURN FROM",
#   ],
#   black      => [
#      "NEW PROCESS",
#      "BEGIN TEST OUTPUT",
#      "END TEST OUTPUT",
#      "RETURN FROM",
#   ],
#   bold       => [
#      "FAIL",
#      "ERROR",
#      "ErrMsg:",
#   ],
);




my $cmd = 'cat ' . $ARGV[0] . ' | sed ';

foreach my $mod (keys %modifications) {
   foreach my $tag (@{$modifications{$mod}}) {
      $cmd .= '-e "s/.*\b' . $tag . '.*/' . $colors{$mod} . '/" ';
   }
}

#foreach my $tag (keys %tags) {
#   $cmd .= '-e "s/.*\b' . $tag . '.*/' . $tags{$tag} . '/" ';
#}


#$cmd .= ' | less -r';
#$cmd .= ' | notepad';

system($cmd);

