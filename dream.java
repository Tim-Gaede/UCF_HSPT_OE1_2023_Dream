// UCF HSPT Online (December 2022) - Candy Tax
// Author - Tyler Marks

import java.util.*;

public class dream{
    
    // declare values
    static int n, k, total;
    static int[] fireballs;
    static int[][][] dp;
    
    public static void main(String[] args) {
        
        // initialize scanner
        Scanner scan = new Scanner(System.in);
        
        // scan in the number of cases
        int numCases = scan.nextInt();
        
        // loop through each case
        for(int c = 0; c < numCases; c++){
            
            // scan in the number of fireballs
            n = scan.nextInt();
            
            // scan in the desired size of the subset
            k = scan.nextInt();
            
            // scan in the fire balls and get the total sum
            fireballs = new int[n];
            total = 0;
            for(int i = 0; i < n; i++){
                fireballs[i] = scan.nextInt();
                total += fireballs[i];
            }
            
            // We have at most 11 bits so we don't
            // care about anything larger than 2 ^ 11
            total = Math.min(total, 1 << 11);
            int ans = -1;
            
            // We can only pick up to 11 items or else some
            // on bits will have to be at the same position
            if(k <= 11){
                
                // initialize a dp array and fill everything to -2.
                // We will do a dp with a state of number of items taken,
                // current fireball index, and the current sum.
                dp = new int[k][n][total];
                for(int i = 0; i < k; i++)
                    for(int j = 0; j < n; j++)
                        Arrays.fill(dp[i][j], -2);
                ans = solve(0, 0, 0);
            }
            
            // Output the answer
            if(ans == -1)
                System.out.println("It do go down");
            else
                System.out.println(ans);
        }
        scan.close();
    }

    public static int solve(int item, int numTaken, int sum){
        // If we have taken k items, return sum.
        if(numTaken >= k)
            return sum;
        
        // If sum surpasses total, or item passes n, it is not possible
        if(item >= n || sum >= total)
            return -1;
        
        // Check to see if we have the current state.
        if(dp[numTaken][item][sum] != -2)
            return dp[numTaken][item][sum];
        
        // try not taking the item
        int leave = solve(item+1, numTaken, sum);
        
        // If the bitwise and of the current fireball
        // and the current sum are 0, then we cannot 
        // take this item so return leave and update the dp table.
        if((sum & fireballs[item]) != 0)
            return dp[numTaken][item][sum] = leave;
        
        // try taking the item
        int take = solve(item+1, numTaken+1, fireballs[item] + sum);
        
        // update the dp table the max of take and leave and return it
        int best = Math.max(leave, take);
        return dp[numTaken][item][sum] = best;
    }
}
