import sys
sys.setrecursionlimit(2022)

# Solution idea: Tyler Hostler-Mathis
# Observe that we can only add a new number to our set
# if it does not share any bits with the current set.
# This means that we can only include each bit at most once,
# and we can place a hard upper bound on our sum at
# 2^(log2(max_ai) + 1)
#
# We will conduct a dynamic programming solution, considering
# adding each fireball one by one (take it or leaev it).
# In order to know what bits we have already included,
# we will also keep our sum.
#
# Just these two states is not enough though, as we also
# need to make sure that we do not take more than k fireballs.
# We cannot simply add a dimension k, as our complexity
# would become too large (~1e9). We can prove that at most
# log2(max_ai) items can be chosen, since they can never share bits.
# This allows us to reduce our k dimension to log2(max_ai)
#
# This results in a dp with dimensions [index][numTaken][sum]
#
# Space and time complexity: n * log2(max_ai) * 2^(log2(max_ai) + 1)
# Note that for simplicity we always make the sum and bit bounds
# of the dp at maximal size, to avoid calculations
# log2(2000) = 11
# 2^(log2(2000) + 1) = 4096

# Max number of bits that can be in numbers relevant to the problem
MAX_BIT = 11
# Space needed to represent all sums
MAX_SUM = 4096
# Low value for invalid DP runs
LOSE = -10000

# Take number of cases
t = int(input())

# For each case
for _ in range(t):
    # Take n and k, and input array
    n, k = map(int, input().split())
    vals = list(map(int, input().split()))

    # If it asks us to take more things than we have bits for
    # we lose
    if k > MAX_BIT:
        print("It do go down")
        continue

    # Create dp size [sum][max_bits][n]
    dp = [[[-1] * MAX_SUM for _ in range(MAX_BIT)] for _ in range(n)]
    def solve(idx, taken, curSum):
        # Took the right amount of k, win!
        if taken >= k:
            return curSum
        # Done with n, but not k, lose
        if idx >= n:
            return LOSE

        # Make sure we are memoizing
        if dp[idx][taken][curSum] != -1:
            return dp[idx][taken][curSum]
        ans = LOSE

        # Check if we can take current
        canTake = (vals[idx] & curSum) == 0

        # Transition
        if canTake:
            ans = max(ans, solve(idx + 1, taken + 1, curSum + vals[idx]))
        ans = max(ans, solve(idx + 1, taken, curSum))

        # Return result
        dp[idx][taken][curSum] = ans
        return ans

    # Get answer and print
    ans = solve(0, 0, 0)
    if (ans == LOSE): print('It do go down')
    else: print(ans)

