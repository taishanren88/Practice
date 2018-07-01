#include <iostream>
#include <vector>
using namespace std;
  struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };
   bool overlaps(Interval a, Interval b)
    {
        if (b.start < a.start) // get the smallest interval
            swap(a,b);
        if (a.end >= b.start)
            return true;
        else
            return false;
    }
    Interval mergeInterval(const Interval& a, const Interval& b)
    {
        Interval result (min(a.start, b.start), max(a.end, b.end));
        return std::move(result);
    }
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        // Insert the interval where appropriate
        // If we found a place to insert it break
        // merge intervals together
        int done = -1;
        if (intervals.empty())
            intervals.push_back(newInterval);
        else
        {
            bool inserted = false;
            for (int i = 0; i < intervals.size(); i++)
            {
                Interval& interval = intervals[i];
                if (inserted)
                    newInterval = intervals[done];
                if (overlaps(newInterval, interval))
                {
                    if (!inserted)
                        done++;
                    intervals[done] = mergeInterval(interval, newInterval);
                    inserted = true;
                }
                else 
                {
                    if (!inserted && newInterval.end < intervals[i].start) // plain insert, easy
                    {
                        done = intervals.size();
                        intervals.insert(intervals.begin() + i,newInterval);
                        break;
                    }
                    else // we're good with this interval, no need to do anything
                    {
                        done++;
                        intervals[done] = intervals[i];
                        // cout <<intervals[done].start <<", " << intervals[done].end <<endl;
                    }
                }
            }
        }

        for (int i = 0; i< done + 1; i++)
            cout << intervals[i].start << ", "<< intervals[i].end<<endl;
        return vector<Interval>(intervals.begin(), intervals.begin() + done + 1);
    }
    
int main()
{
    vector<Interval> test = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    //{1,2} ,{3,10} , {12,16}
    insert(test, Interval(4,8));
}
