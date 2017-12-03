# Gregory Mann
# Fall 2017
# COSC 341
# Project 4

while (true) {
    print "1: quadratic\n";
    print "2: prime\n";
    print "3: compute pi\n";
    print "4: tax\n";
    print "5: idpassword\n";
    print "6: score\n";
    print "7: filesort\n";
    print "8: frequency\n";
    print "9: power\n";
    print "10: factorial\n";
    print "11: sort\n";
    print "12: minmax\n";
    print "13: positives\n";
    print "14: fractionals\n";
    print "15: emuid\n";
    print "16: emuweb\n";
    print "17: whitespace\n";
    print "18: areacode\n";
    print "q: quit\n";

    $input = <STDIN>;

    if ($input == 1) {
        quadratic();
    } elsif ($input == 2) {
        prime();
    } elsif ($input == 3) {
        pi();
    } elsif ($input == 4) {
        tax();
    } elsif ($input == 5) {
        idpassword();
    } elsif ($input == 6) {
        score();
    } elsif ($input == 7) {
        filesort();
    } elsif ($input == 8) {
        frequency();
    } elsif ($input == 9) { # For power function.
        print "Power function\n";

        print "Input the base\n";
        my $base = <STDIN>;
        chomp($base);

        print "Input the exponent\n";
        my $exponent = <STDIN>;
        chomp($exponent);

        print "$base to the power of $exponent is: " . power($base, $exponent) . "\n";
    } elsif ($input == 10) { # For factorial function.
        print "Enter a number to factorial\n";
        my $num = <STDIN>;
        chomp($num);
        print "The factorial of $num is: " . factorial($num) . "\n";
    } elsif ($input == 11) { # For sort function.
        print "Enter a list of numbers seperated by spaces.\n";
        my $in = <STDIN>;
        chomp($in);

        @numbers = split(/ /, $in);
        &my_sort(@numbers);

        print "Sorted:\n";
        foreach $num (@numbers) {
            print "$num ";
        }
        print "\n";
    } elsif ($input == 12) { # For minmax function.
        print "Enter a list of numbers seperated by spaces.\n";
        my $in = <STDIN>;
        chomp($in);

        @numbers = split(/ /, $in);

        my $min;
        my $max;

        minmax(@numbers, $min, $max);

        print "The min is $min the max is $max.\n";
    } elsif ($input == 13) {
        positives();
    } elsif ($input == 14) {
        fractionals();
    } elsif ($input == 15) {
        emuid();
    } elsif ($input == 16) {
        emuweb();
    } elsif ($input == 17) {
        whitespace();
    } elsif ($input == 18) {
        areacode();
    } else {
        last;
    }

}

# ------------------------------------------------------------------------------

# Solves the quadratic equation given a, b, and c from the user
# prints out the solutions or a message indicating that no real solutions exist.
sub quadratic {
    print "Input a, b, and c on seperate lines.\n";
    my $a = <STDIN>;
    chomp($a);
    my $b = <STDIN>;
    chomp($b);
    my $c = <STDIN>;
    chomp($c);

    my $discriminate = ($b * $b) - (4 * $a * $c);

    if ($discriminate < 0) {
        print "Quadratic $a, $b, $c has no solutions.\n";
    } else {
        my $sol1 = (($b - (2 * $b)) + sqrt($discriminate)) / (2 * $a);
        my $sol2 = (($b - (2 * $b)) - sqrt($discriminate)) / (2 * $a);
        print "The solutions are $sol1, and $sol2\n";
    }
}

# ------------------------------------------------------------------------------

# Decides wheather a number is prime or not and displays the result.
sub prime {
    my $i;

    print "Please input a number to check if it's prime.\n";
    my $in = <STDIN>;
    chomp($in);

    for ($i = 2; $i < $in -1; $i++) {
        if (!($in % $i)) {
            print "$in is not prime\n";
            return; # Stop iterating.
        }
    }
    print "$in is prime\n";
}

# ------------------------------------------------------------------------------

# Computes the constant pi using a talor series up to the specified iteration.
sub pi {
    my $term;
    my $i;
    my $pi = 0;

    print "How many iterations of the talor series would you like to compute?\n";
    my $in = <STDIN>;
    chomp($in);

    for ($i = 0; $i < $in; $i++)
    {
        # Compute value of the term.
        $term = 1 / (1.0 + $i * 2);

        # Alternate between adding and subtracting the term by using i % 2.
        if ($i % 2) {
            $pi -= $term;
        }
        else {
            $pi += $term;
        }
    }

    $pi = 4 * $pi;

    print "pi at $in iterations is $pi.\n";
}

# ------------------------------------------------------------------------------

# A sub program that calculates the amount of tax you pay.
# Reads in the marital status, income, and residency of the user.
sub tax {
    my $rate;
    my $tax_increase;

    print "What is your marital status? (married or single)\n";
    my $marital_status = <STDIN>;
    chomp($marital_status);

    print "What is your income? (e.g. 40000)\n";
    my $income = <STDIN>;
    chomp($income);

    print "Are you in state or out of state? (i or o)\n";
    my $state = <STDIN>;
    chomp($state);

    # Set the initial tax amount and set the value for the next tax
    # bracket based on marital status.
    if (($marital_status eq "MARRIED") || ($marital_status eq "married")) {
        $rate = 0.10;
        $tax_increase = 50000;
    } else { # Only an else here because we arnt doing error handling this time.
        $rate = 0.20;
        $tax_increase = 30000;
    }

    # Increase the tax amount if your income is enough to put you in
    # the next tax bracket.
    if ($income >= $tax_increase) {
        $rate += 0.05;
    }

    # Reduce the tax amount if your out of state.
    if ($state eq "O" || $state eq "o") {
        $rate -= 0.03;
    }

    my $tax_amount = $income * $rate;

    print "You tax amount is: \$$tax_amount\n";
}

# ------------------------------------------------------------------------------

# This function prompts the user for first name and last name and
# prints a user id and password.
sub idpassword {
    print "Generating id and password.\n";

    print "Please enter your first name.\n";
    my $first_name = <STDIN>;
    chomp($first_name);

    my @first_name_chars = split(//, $first_name);
    my $first_name_length = @first_name_chars;

    print "Please enter your last name.\n";
    my $last_name = <STDIN>;
    chomp($last_name);

    my @last_name_chars = split(//, $last_name);
    my $last_name_length = @last_name_chars;

    # Generate user id.
    my $user_name = uc($first_name_chars[0] . $last_name);

    print "User id: $user_name\n";

    # Generate password.
    my $password =
        # First and last letter of the first name.
        $first_name_chars[0] . $first_name_chars[first_name_length - 1] .
        # First 3 letters of the last name.
        $last_name_chars[0] . $last_name_chars[1] . $last_name_chars[2] .
        # Length of first name.
        $first_name_length .
        # Length of last name.
        $last_name_length;

    # Uppercase password.
    $password = uc($password);

    print "Password: $password\n";
}

# ------------------------------------------------------------------------------

# Score reads in student names and scores from the user and prints out
# the best student, best score, worst student, worst score, and the
# avarage score.
sub score {
    # Reads in student names and scores give the avarage and the min and max scores.
    my $best_student;
    my $best_score = -99999999999;

    my $worst_student;
    my $worst_score = 99999999999;
    my $avarage = 0;

    my $input;
    my @name_score_pair;

    my $count = 0;

    print "Enter student names and scores.\n
E.g.\n
> Jane 90\n
Enter q to quit.\n";

    while (true) {
        $input = <STDIN>;
        chomp($input);

        @name_score_pair = split(/ /, $input);

        # Break out of the loop if the user enters q.
        if ($name_score_pair[0] eq "q" || $name_score_pair[0] eq "Q") {
            last;
        }

        # Increment count.
        $count++;

        $avg += $name_score_pair[1];

        if ($name_score_pair[1] > $best_score) {
            $best_student = $name_score_pair;
            $best_score = $name_score_pair[1];
        }

        if ($name_score_pair[1] < $worst_score) {
            $worst_student = $name_score_pair;
            $worst_score = $name_score_pair[1];
        }
    }

    $avg = $avg / $count;

    # Print out the information.
    print "The best student is $best_student with a score of $best_score.\n";
    print "The worst student is $worst_student with a score of $worst_score.\n";
    print "The avarage score was $avg.\n";
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the records
# from the input file to the output file sorted by last name.
sub filesort {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    my @records = <FIN>;
    my @current_record;
    my @comp_record;
    my $lowest_index;
    my $temp;

    # Selection sort.
    for (my $i = 0; $i < @records; $i++) {

        $lowest_index = $i;

        # Break the record into bits so I can compare the last names.
        @current_record = split(/ /, $records[$lowest_index]);

        for (my $j = $i; $j < @records; $j++) {

            # Break the record into bits so I can compare the last names.
            @comp_record = split(/ /, $records[$j]);

            if ($comp_record[0] lt $current_record[0]) {
                $lowest_index = $j;

                # Break the record into bits so I can compare the last names.
                @current_record = split(/ /, $records[$lowest_index]);
            }
        }

        # Swap the records.
        $temp = $records[$i];
        $records[$i] = $records[$lowest_index];
        $records[$lowest_index] = $temp;
    }

    # Write the lines to the outfile.
    foreach $line (@records) {
        print FOUT $line;
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Takes an input file from the user and prints out the frequencies of
# the last names in the file.
sub frequency {
    print "Please enter a filename \n";
    my $filename = <STDIN>;
    chomp($filename);

    my $line;
    my %last_names;
    my @last_first_pair;

    # Open the file for reading.
    open(FIN, "<$filename");

    while ($line = <FIN>) {
        my @last_first_pair = split(/ /, $line);

        $last_names{$last_first_pair[0]}++;
    }

    close(FIN);

    # Print out the frequencies.
    print "Frequencies:\n";

    foreach $key (keys(%last_names))  {
        print "$key: " . $last_names{$key} . "\n";
    }
}

# ------------------------------------------------------------------------------

# Takes two parameters x and y, reutrns x to the power of y.
sub power {
    my $x = $_[0];
    my $y = $_[1];

    $result = 1;

    for ($i = 0; $i < $y; $i++) {
        $result = $result * $x;
    }

    return $result;
}

# ------------------------------------------------------------------------------

# Takes a single input and returns the factorial of that number.
sub factorial {
    my $n = $_[0];

    if ($n == 1) {
        return 1;
    } else {
        return $n * factorial($n -1);
    }
}

# ------------------------------------------------------------------------------

# Takes an integer array and sorts it.
# Sort is a built in function so I named this to my_sort
sub my_sort {
    my $lowest_index;
    my $temp;

    # Selection sort.
    for ($i = 0; $i < @_; $i++) {

        $lowest_index = $i;

        for ($j = $i; $j < @_; $j++) {
            if ($_[$j] < $_[$lowest_index]) {
                $lowest_index = $j;
            }
        }

        # Swap the elements.
        $temp = $_[$i];
        $_[$i] = $_[$lowest_index];
        $_[$lowest_index] = $temp;
    }
}

# ------------------------------------------------------------------------------

# Takes an array and a min and max variables, and changes the min and
# max parameters to the min and max of the array.
sub minmax {
    my $len = @_ - 2;
    my $min_loc = $len;
    my $max_loc = $len +1;

    # Initialize min and max to zero.
    $_[$max_loc] = $_[0];
    $_[$min_loc] = $_[0];

    for ($i = 0; $i < $len; $i++) {
        # If its bigger set max.
        if ($_[$i] > $_[$max_loc]) {
            $_[$max_loc] = $_[$i];
        }
        # If its less then set min.
        if ($_[$i] < $_[$min_loc]) {
            $_[$min_loc] = $_[$i];
        }
    }
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the positive
# integers from the input file to the output file.
sub positives {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        if ($line =~ /^[1-9][0-9]*$/) {
            print "what? $line\n";
            print FOUT $line;
        }
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the
# fractionals from the input file to the output file.
sub fractionals {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        if ($line =~ /^0.[0-9]*$/) {
            print FOUT $line;
        }
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the
# words that are in emuid format to the outfile.
sub emuid {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        if ($line =~ /^(e|E)00[0-9][0-9][0-9][0-9][0-9]$/) {
            print FOUT $line;
        }
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the
# words that are in emuweb format to the outfile.
sub emuweb {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        if ($line =~ /^www\.emich\.edu\/([a-zA-z]+\/)*[a-zA-z]+\.html$/) {
            print FOUT $line;
        }
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and writes the records
# back to the file with a single space between the first and last name.
sub whitespace {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        $line =~ s/[ \t]+/ /g;
        print FOUT $line;
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------

# Asks the user for an input and output file and replaces the areacode
# 715 with 692 and writes it to the output file.
sub areacode {
    print "Please enter the input file name\n";
    my $infile = <STDIN>;
    chomp($infile);

    print "Please enter the output file name\n";
    my $outfile = <STDIN>;
    chomp($outfile);

    open(FIN, "<$infile");
    open(FOUT, ">$outfile");

    # If the line matches the expression print it to the outfile.
    while ($line = <FIN>) {
        $line =~ s/ 715/ 692/g;
        print FOUT $line;
    }

    close(FIN);
    close(FOUT);
}

# ------------------------------------------------------------------------------
