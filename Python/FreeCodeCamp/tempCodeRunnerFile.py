hour_begin, minute_begin = [int(x) for x in start_time.split(":")]
    if am_or_pm == "PM":
        hour_begin += 12
    start_seconds = hour_begin * 3600 + minute_begin * 60

    delta_hour, delta_minute = [int(x) for x in duration.split(":")]
