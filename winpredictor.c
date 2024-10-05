#include <stdio.h>

// Function to calculate the winning probability based on some factors
float calculate_win_probability(int runs_chasing, int runs_needed, int overs_left, int wickets_lost) {
    // Calculating the current run rate and required run rate
    float current_run_rate = (float)runs_chasing / (50 - overs_left);
    float required_run_rate = (float)runs_needed / overs_left;

    // Basic prediction logic
    float win_probability;

    if (wickets_lost >= 9) {
        // If 9 or more wickets are lost, chances of winning are very low
        win_probability = 5.0;
    } else {
        // Simplified calculation based on required run rate and wickets lost
        if (current_run_rate >= required_run_rate) {
            win_probability = 70 - (wickets_lost * 5); // Less wickets means better chances
        } else {
            win_probability = 40 - (wickets_lost * 5); // More wickets reduce chances of winning
        }
    }

    // Ensuring the probability is within 0-100% range
    if (win_probability > 100) {
        win_probability = 100;
    }
    if (win_probability < 0) {
        win_probability = 0;
    }

    return win_probability;
}

int main() {
    int first_target, runs_needed, overs_left, wickets_lost;
    
    // Input data
    printf("Enter the runs scored by the first team: ");
    scanf("%d", &first_target);

    printf("Enter the runs needed by the chasing team: ");
    scanf("%d", &runs_needed);

    printf("Enter the overs left: ");
    scanf("%d", &overs_left);

    printf("Enter the number of wickets lost: ");
    scanf("%d", &wickets_lost);

    // Calculate win probability
    float win_probability = calculate_win_probability(first_target, runs_needed, overs_left, wickets_lost);

    // Display win probability
    printf("The win probability for the chasing team is: %.2f%%\n", win_probability);

    return 0;
}

