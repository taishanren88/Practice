#!/usr/bin/env python2

# make sure to install these packages before running:
# pip install pandas
# pip install sodapy

import pandas as pd
from sodapy import Socrata
from datetime import datetime
from requests.exceptions import ConnectionError
import json

# Returns day of week based on 0-> Monday, 6 -> Sunday
def get_day_of_week(day_index):
	weekdays = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
	#print ('week day is ' + weekdays[day_index])
	return weekdays[day_index]

# Returns current time as "HH:MM"
def get_current_time():
	dateTimeObj = datetime.now()
	timestampStr = dateTimeObj.strftime("%H:%M")
	#print('current time is ' + timestampStr)
	return timestampStr

# Print the SF City Food truck data pertaining to currently open food trucks
def print_sf_foodtruck_data():
	currentTime = get_current_time()
	day_index = datetime.today().weekday()
	try:
		client = Socrata("data.sfgov.org", None)
		# Get the data in JSON format, for today's date
		# Ensure open/close time includes the current time 
		# Finally sort by applicant name
		results = client.get("jjew-r69b", content_type="json", dayofweekstr=get_day_of_week(day_index),
						where='start24 <= "'  + currentTime + '" and end24 >= "' + currentTime + '"', 
						order="applicant ASC")

		# Note there are multiple applicants under same name, since they could be in different locations
		count = 0
		for result in results:
			# Stop every 10 results and wait for user input
			if count == 10:
				name = raw_input("Press any key to get the next set of results ")
				count = 0
			print(result["applicant"] + ' ' + result["location"])
			count = count + 1
			#print(json.dumps(result, indent = 4))

		client.close()
	except ConnectionError as err:
		print("HTTP connection error: ", err)
	except:
		print("Unexpected error:", sys.exc_info()[0])

def main():
	print_sf_foodtruck_data()

if __name__ == "__main__":
	main()