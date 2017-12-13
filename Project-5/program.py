# Gregory Mann
# Fall 2017
# COSC 341
# Project 1

# --------------------------------------------------------------------------------

# Computes pi with the formula 4(1 - 1/3 + 1/5 - 1/7 + 1/9...) up to
# the nth term.
def compute_pi(n):
    pi = 0.0
    term = 0.0

    for i in range(0, n):
        # Compute value of the term.
        term = 1 / (1.0 + i * 2)

        # Alternate between adding and subtracting the term by using i % 2
        if i % 2:
            pi -= term
        else:
            pi += term

    return 4 * pi

# --------------------------------------------------------------------------------

# Computes the square root of the input x.
def compute_sqrt(x):
    guess = 1;

    for i in range(0, 10):
        guess = 0.5 * (guess + x / guess);

    return guess;

# --------------------------------------------------------------------------------

# Determines if the input n is prime or not.
def is_prime(n):

    # If n is divisible by any number greater than 2 and less than
    # itself then return false.

    # Yes I know this is really really slow.
    for i in range(2, n):
        if n % i == 0:
            return False

    return True

# --------------------------------------------------------------------------------

# Displays all the prime numbers up to and including n.
def display_primes(n):
    print("Primes are: ")

    # For every number between 2 and n check to see if it's prime. If
    # it is print it out.
    for i in range(2, n + 1):
        if is_prime(i):
            print(str(i) + ' ', end = '')

    print('') # Just print out the newline character.

# --------------------------------------------------------------------------------

# This function asks the user to input a list of student score pairs.
# It then displays the average score, best score, best scoring
# student, worst score, and the worst scoring student.
def process_scores():

    # Setting up some variables.
    avg = 0
    number_of_students = 0
    best_score = -9999999999999999
    worst_score = 9999999999999999

    print("Enter student names and scores.\n\
E.g.\n\
> Jane 90\n\
Enter 'q' to quit.")

    while True:
        line = input("> ")

        if line == 'q':
            break

        line = line.split()

        name = line[0]
        score = int(line[1])

        # If the current score is the best one set the best name and the
        # best score.
        if score > best_score:
            best_student = name
            best_score = score

        # If the current score is the worst one set the worst name and
        # the worst score.
        if score < worst_score:
            worst_student = name
            worst_score = score

        avg += score
        number_of_students += 1

    print("The avarage score is: " + str(avg / number_of_students))
    print(best_student + " has the best score " + str(best_score))
    print(worst_student + " has the worst score " + str(worst_score))

# --------------------------------------------------------------------------------

# This function computes some imaginary tax rules and returns the
# percentage that your going to be taxed.
def compute_tax(income, status, state):
    rate = -1.0
    tax_increase = 9999999999999999

    # Set the initial tax amount and set the value for the next tax
    # bracket based on marital status.
    if status.upper() == "MARRIED":
        rate = 0.10
        tax_increase = 50000
    else:
        rate = 0.20
        tax_increase = 30000

    # Increase the tax amount if your income is enough to put you in
    # the next tax bracket.
    if income >= tax_increase:
        rate += 0.05

    # Reduce the tax amount if your out of state.
    if state.upper() == 'O':
        rate -= 0.03

    return income * rate;

# --------------------------------------------------------------------------------

# The "Main" of the program.
print("1. Compute Pi\n\
2. Compute Square Root\n\
3. Find Prime Numbers\n\
4. Process Scores\n\
5. Compute Tax\n\
Enter 'q' to quit.")

while True:
    user_input = input("\nPlease select an option: ")

    # Compute Pi.
    if user_input == '1':
        user_input = input("Please enter the number of iterations: ")

        print("Pi to " + user_input + " iterations is: "
              + str(compute_pi(int(user_input))))

    # Square root.
    elif user_input == '2':
        user_input = input("Please enter a number to square: ")

        print("The square of " + user_input + " is: "
              + str(compute_sqrt(int(user_input))))

    # Prime numbers.
    elif user_input == '3':
        user_input = input("Enter the number you would like to find primes up to: ")

        display_primes(int(user_input))

    # Process scores.
    elif user_input == '4':
        process_scores()

    # Compute tax.
    elif user_input == '5':
        print("Computing Tax")

        income = input("Enter your income: ")
        status = input("Enter your marital status (Married or Single): ")
        state = input("Enter your state residency (i/o): ")

        print("Your tax amount is $"
              + str(compute_tax(int(income), status, state)))

    elif user_input == 'q':
        break
