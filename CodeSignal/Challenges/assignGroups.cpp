/*Mr. Hudson is teaching a course on algorithms at computer school. He's assigning his class a project that involves a group presentation. Each presentation will happen one at a time and the groups can have as many as groupSize members.

Based on prior experience, Mr. Hudson has a list of estimates for each of the students, representing the minimum number of minutes that a presentation will take if that student is part of the group. These time estimates are stored in an array timeEstimates (For confidentiality reasons, the students' names have been anonymized, so it's just the number of minutes each will take).

Mr. Hudson wants to take up as little class time as possible for the whole class to give their presentations. Return the total minimum number of minutes the presentations will be expected to take if the groups are assigned in such a way that the estimated total time is minimized.

Example

    For timeEstimates = [12, 7, 3, 6, 5, 6, 10, 3, 9, 6] and groupSize = 3, the output should be assignGroups(timeEstimates, groupSize) = 28.

    Here's one way the groups could be assigned for a minimal total time:
    example image

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.integer timeEstimates

    An array of integers where timeEstimates[i] represents the minimum number of minutes a presentation will take if the student represented by index i is involved.

    Guaranteed constraints:
    0 ≤ timeEstimates.length ≤ 3 · 105
    0 ≤ timeEstimates[i] ≤ 108

    [input] integer groupSize

    An integer representing the maximum number of students that each group can have.

    Guaranteed constraints:
    1 ≤ groupSize ≤ 108

    [output] integer

    An integer representing the minimum total length of time (in minutes) the presentations will take.
*/

int r=0, i=0, assignGroups(auto t, int g) {
    sort(t.rbegin(), t.rend());
    for (; i<t.size(); i+=g)
        r += t[i];
    
    return r;
}
