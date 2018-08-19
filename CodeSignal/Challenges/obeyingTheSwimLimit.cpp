/*Summer's here! You can't think of a better way to spend the day than going for a swim at the local beach! However, the normal lifeguard (let's call him Larry) isn't on duty. It's his pain of an accomplice, Robert.

Now Bob is pretty strict. Rumor has it that he can't swim. Therefore, to protect himself, he enforces a strict no swimming after eating rule. Here are the parts of the rule:
Calories Consumed 	Time to Wait (minutes)
0-600 	0
601-1400 	15
1401-2000 	30
2001+ 	60

Given an array of various foods eaten, output how long you should wait before swimming.
Food 	Calories
Banana 	100
Apple 	80
Pizza 	300
Chocolate 	500
Roast Beef 	850
Milk 	110
Chicken 	300
Deluxe Burger 	1000

    [execution time limit] 0.5 seconds (cpp)

    [input] array.string intake

    An array of the foods you ate.

    Guaranteed Constraints
    0 ≤ intake.length ≤ 10
    intake[i] ∈ ["Banana", "Apple", "Pizza", "Chocolate", "Roast Beef", "Milk", "Chicken", "Deluxe Burger"]

    [output] integer

    How long you should wait (in minutes) before swimming.
*/

int r = 0, obeyingTheSwimLimit(auto v) {
    map<string, int> c     {{"Banana",         100},
                            {"Apple",           80},
                            {"Pizza",          300},
                            {"Chocolate",      500},
                            {"Roast Beef",     850},
                            {"Milk",           110},
                            {"Chicken",        300},
                            {"Deluxe Burger", 1e3}};
    
    for (auto s: v) r += c[s];
    
    return r < 601 ? 0 : r < 1401 ? 15 : r < 2001 ? 30 : 60;
}
