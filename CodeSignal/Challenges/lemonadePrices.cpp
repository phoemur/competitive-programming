/*Getcha Lemonade Here!

You are a kid trying to get a head start to pay for college. (Good. Luck.) So, this summer, you decide to run a lemonade stand! However, you don't know what to charge yet. Your parents tell you to experiment and start with the prices high. They also tell you to change them based on gradually descending percentages, so you can learn math during the summer! Eww! (They are evil.)

Each day you decide to change the percentages at a constant rate between 0.1% and 50.0%, to get a better feel of the right price. For example, if the price on the second day is 97% of the first day's price, then the third day will be 94% of the second day, the fourth will be 91% of the third, etc.

You keep a log of each day's price, as well as how many lemonades were sold that day. Unfortunately, after a few days, you forgot to keep logging the prices, so some of them are missing.

Given prices, an incomplete list of daily prices, and quantity, a complete list of lemonades sold per day, your task is to find the amount earned from total lemonade sales.

To help resolve rounding issues, your logs have rounded the prices to 2 decimals places each day, and you want the output to be printed in string format with 2 decimal places with no commas.

Examples

    For prices = [10, 9.5, 8.55, 7.27] and quantity = [10, 15, 20, 30, 40], the output should be lemonade_prices(prices, quantity) = "864.40".

    You can visualize the data given as below:
    Days 	Prices 	Quantity 	Sub-Total
    0 	10 	10 	100.00
    1 	9.5 	15 	142.50
    2 	8.55 	20 	171.00
    3 	7.27 	30 	218.10
    4 	5.82 	40 	232.80
    		Total 	864.40

    The percentage seems to be declining by 5% each day: 9.5 is 95% of 10, 8.55 is 90% of 9.5, 7.27 is 85% of 8.55, and so the next price should be 80% of 7.27 (which is 5.82).

    Multiplying each price by the corresponding quantity, we get a total revenue of "864.40".

    For prices = [12, 11.16, 9.6, 7.58, 5.46] and quantity = [3, 4, 3, 9, 12, 15, 20, 34], the output should be "373.33".

    In this case, you have to find the 3 missing prices and then provide the expected sum.

    You can visualize the data given as below:
    Days 	Prices 	Quantity 	Sub-Total
    0 	12 	3 	36.00
    1 	11.16 	4 	44.64
    2 	9.6 	3 	28.80
    3 	7.58 	9 	68.22
    4 	5.46 	12 	65.52
    5 	3.55 	15 	53.25
    6 	2.06 	20 	41.20
    7 	1.05 	34 	35.70
    		Total 	373.33

    Once you are able to find the pattern (percentages declining by 7% each day), you are able to get the expected output "373.33".

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.float prices

    An array of floating point values representing the prices of your lemonade for each day, based on the pattern described above. It's guaranteed that at least one day's prices are missing.

    Guaranteed constraints:
    2 ≤ prices.length < quantity.length
    0 < prices[i] < 5 · 104

    [input] array.integer quantity

    An array of integers representing how many lemonades were sold each day (no pattern necessary).

    Guaranteed constraints:
    3 ≤ quantity.length < 20
    0 < quantity[i] < 1000

    [output] string

    The predicted sum, represented as currency (as a string with 2 decimal places). For example, 12 is "12.00", 9.5 is "9.50", and 1234.555 is "1234.56".
*/

string lemonadePrices(vector<double>& prices, const vector<int>& quantity) 
{
    double dec = 1 - prices[1] / prices[0];
    double perc_acc = 1.0 - dec * (prices.size() - 1);
    
    // Generate the missing prices
    generate_n(back_inserter(prices), 
               quantity.size() - prices.size(), 
               [&]()
               {
                   return round(prices.back() *
                                // Beware of the comma operator //
                               (perc_acc -= dec, perc_acc) * 100) / 100;
               });
    
    
    // The result is the dot product
    ostringstream result;
    
    result << setprecision(2) 
           << fixed 
           << inner_product(begin(prices), end(prices), begin(quantity), 0.0);
    
    return result.str();
}
