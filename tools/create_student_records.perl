#! /usr/bin/perl
use strict;
use warnings;
use v5.20.2;
use Data::Dump qw/dump/;
use File::Slurper qw/read_lines/;
use Getopt::Long;
use autodie qw(:all);
use Log::Any qw($log);
use Log::Dispatch;
use Log::Any::Adapter;
use List::Util qw(shuffle);

sub init_logging {
    # Send all logs to Log::Dispatch
    my $dispatch_logger = Log::Dispatch->new(
        outputs => [
            [ 'Screen', min_level => 'debug', newline => 1 ],
        ],
    );
    Log::Any::Adapter->set('Dispatch', dispatcher => $dispatch_logger);
}

init_logging();
$log->debugf("arguments are: %s", "foo");


my $data   = "file.dat";
my $length = 24;
my $verbose;

GetOptions ("length=i" => \$length,    # numeric
            "file=s"   => \$data,      # string
            "verbose"  => \$verbose)   # flag
    or die("Error in command line arguments\n");

sub random_percentage {
    return int(rand(100));
}

sub main {
    my ($n_records) = @_;

    my @lastnames = read_lines("data/lastnames.csv", 'UTF-8', 1);
    pop @lastnames;
    @lastnames = shuffle(@lastnames);

    my $n_homeworks = 4;

    for my $i (1..$n_records) {
        my $name = pop @lastnames;

        my $midterm = int(rand(100));
        my $final = int(rand(100));

        my @homeworks;
        for my $j (1..$n_homeworks) {
            push @homeworks, random_percentage();
        }

        say "$name $midterm $final @homeworks";
    }
}

main @ARGV;
