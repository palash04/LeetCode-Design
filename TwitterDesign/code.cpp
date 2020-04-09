#include <bits/stdc++.h>
using namespace std;

class Twitter {
    int timeStamp;
    map<int, vector<pair<int,int>>> userMap;
    map<int, set<int>> followerMap;
public:
    /** Initialize your data structure here. */
    Twitter() {
        timeStamp = 0;
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        timeStamp++;
        if (userMap.find(userId) == userMap.end()){
            vector<pair<int, int>> tweet;
            tweet.push_back({timeStamp, tweetId});
            userMap.insert({userId,tweet});
        }else{
            userMap[userId].push_back({timeStamp,tweetId});
        }
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        int orgUserId = userId;
        vector<int> tweets;
        vector<pair<int,int>> allTweets;
        if (userMap.find(userId) == userMap.end()){
            return vector<int>();
        }
        
        allTweets = userMap[userId];
        
        queue<int> q;
        
        set<int> follo;
        follo = followerMap[userId];
        
        for (auto f : follo){
            q.push(f);
        }
        while (!q.empty()){
            userId = q.front();
            q.pop();
            vector<pair<int, int>> thisTweets = userMap[userId];
            for (auto tweet : thisTweets){
                allTweets.push_back(tweet);
            }
        }
        
        sort(allTweets.begin(), allTweets.end());
        int tweetNo = 10;
        int n = (int)allTweets.size();
        while (tweetNo-- && n--){
            tweets.push_back(allTweets[n].second);
        }
        return tweets;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        if (userMap.find(followerId) == userMap.end()){
            vector<pair<int,int>> tweet;
            userMap.insert({followerId,tweet});
        }
        
        if (followerMap.find(followerId) == followerMap.end()){
            set<int> followers{followeeId};
            followerMap.insert({followerId,followers});
        }else{
            followerMap[followerId].insert(followeeId);
        }

    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (followerMap.find(followerId) != followerMap.end()){
            followerMap[followerId].erase(followeeId);
        }
    }
};
