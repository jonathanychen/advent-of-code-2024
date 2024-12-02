with open("inputs/input.txt", "r") as f:
    result = 0
    for line in f.readlines():
        nums = line.split()

        nums = [int(n) for n in nums]

        if list(sorted(nums)) != nums and list(reversed(sorted(nums))) != nums:
            continue

        first_diff = nums[1] - nums[0]
        if first_diff == 0:
            continue

        increasing = first_diff > 0

        valid = True

        for i in range(1, len(nums)):
            diff = nums[i] - nums[i-1]
            if diff == 0:
                valid = False
                break

            curr_increasing = diff > 0
            if curr_increasing != increasing:
                valid = False
                break

            diff = abs(diff)
            if not (diff >= 1 and diff <= 3):
                valid = False
                break
        
        if valid: result += 1

    print("Day 2 -- Part 1:", result)

with open("inputs/input.txt", "r") as f:
    result = 0
    for line in f.readlines():
        nums = line.split()

        nums = [int(n) for n in nums]        

        def test_list(arr):
            if list(sorted(arr)) != arr and list(reversed(sorted(arr))) != arr:
                return False

            first_diff = arr[1] - arr[0]
            if first_diff == 0:
                return False

            increasing = first_diff > 0

            for i in range(1, len(arr)):
                diff = arr[i] - arr[i-1]
                if diff == 0:
                    return False

                curr_increasing = diff > 0
                if curr_increasing != increasing:
                    return False

                diff = abs(diff)
                if not (diff >= 1 and diff <= 3):
                    return False
            
            return True
        
        if test_list(nums):
            result += 1
            continue

        for i in range(len(nums)):
            test = nums[:i] + nums[i+1:]

            if test_list(test):
                result += 1
                break

    print("Day 2 -- Part 2:", result)
