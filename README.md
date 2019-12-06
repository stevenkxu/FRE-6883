# FRE-6883

Group consisting of Steven, Xiongan, Zhitong, Lisa, and Ning

Note: create windows and mac staging environments so we can actually test the code as it's done

## Tasks and deadlines
### ~~Pull earnings dates and values from Bloomberg for S&P500 stocks:~~ Done
Xiongan, End-of-day 12/4
- Calculate Surprise
- Sort Surprise into Beat, Meet, Miss

Status summary: 
Beat, meet, miss are in 3 separate csv files with earnings surprise as percentage for each row. *As far as I can tell* the only thing we care about from each of these stocks is what group they are categorized in and when their earnings reporting date was. For the next part, import the file EquityDivide.h and tools.h. Create a pointer to instance of EquityDivide and use the function divide_group, we can get the 3 groups which are stored in a dataype like this, vector<vector<pair<Ticker, Date>>>. The dimension of this datatype is (3, size of each group, 2).

### Sample 30 stocks from each of 3 groups (90 total):
Steven and Zhitong, Friday afternoon 12/6
 - ~~Sample 30 stocks from each of 3 groups randomly (probably done)~~
 - Download 61 days of data for SPY and the sampled stocks around the earnings date. Cache these so the download only needs to be done once for each stock. OR: download all 500 at once. 
 -- How to do? map of <string, vector> where string is ticker and vector is price at date. Either send request to Yahoo in one block, or send 60+ requests per stock to make sure that we get 60 data points
 - Prepare a loop that will do this, and the following block, 30 times.
 
 ### Calculate statistics from collected data:
 Lisa and Ning, Monday afternoon 12/9
 - Make sure the code is suited for repeating 30 times! This will be a Monte Carlo simulation
 - Calculate returns on all stocks and SPY per day, per stock.
 - Calculate abnormal return on all stocks, per day.
 - For each group (Beat, Meet, Miss), for each day, calculate average daily abnormal return (AAR) of all stocks in that day.
 - Calculate Cumulative AAR (CAAR)
 - Make sure the code is suited for repeating 30 times! This will be a Monte Carlo simulation
 - After running code 30 times (with 30 different randomly selected stocks each time), average the AAR and CAAR for each day across all runs, and the standard deviation of each day across all runs.
 
 ### Plot data
 TBD, Before Tuesday 12/10 if possible, by Thursday 11/12 at latest.
 - Using gnuplot, plot the data.
 
 ## Final deadline: 12/14
