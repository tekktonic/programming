def hrsize(num):

    tmp = int(num)
    if tmp / 1024 > 1: # kilobytes
        if tmp / 1024 / 1024 > 1: # megabytes
            return str(tmp / 1024 / 1024) + " MB"# wipe any remaining characters
        else:
            return str(tmp / 1024) + " KB"

    else: # bytes, really not needed....
        return str(tmp) + " B"
