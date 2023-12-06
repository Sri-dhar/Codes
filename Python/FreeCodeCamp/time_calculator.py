def add_time(start, duration, day=None):
    days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]

    start_time, am_or_pm = start.split()
    hour_begin = int(start_time.split(":")[0])
    minute_begin = int(start_time.split(":")[1])
    if am_or_pm == "PM":
        hour_begin += 12
    start_seconds = hour_begin * 3600 + minute_begin * 60

    delta_hour, delta_minute = map(int, duration.split(":"))
    duration_seconds = delta_hour * 3600 + delta_minute * 60

    final_seconds = (start_seconds + duration_seconds) % (24 * 3600)

    final_hour = final_seconds // 3600
    final_minute = (final_seconds % 3600) // 60
    final_am_or_pm = "AM" if final_hour < 12 else "PM"
    if final_hour > 12:
        final_hour -= 12

    result_time = f"{int(final_hour)}:{final_minute:02d} {final_am_or_pm}"

    delta_days = (start_seconds + duration_seconds) // (24 * 3600)
    

    if day is not None:
        day = day.lower().capitalize()
        day_index = (days.index(day) + delta_days) % 7
        result_time = f"{result_time}, {days[day_index]}"

    if delta_days == 1:
        result_time += " (next day)"
    elif delta_days > 1:
        result_time += f" ({delta_days} days later)"

    return result_time


actual = add_time("8:16 PM", "466:02", "tuesday")
print(actual)
