# export_json.R
# 
# This scirpt import content of a csv file into a dataframe then convert it into
# a json object before saving it in JSON file format
# 
# Required package:
#         jsonlite
# 
# Last modified: 2016-09-12  
# By: Nanda Khaorapapong
# Contact: nandadoes@gmail.com  
#    
# Copyright (c) 2016 Nanda Khaorapapong and Connected Seeds  
# License: GNU GPLv3 license <https://www.gnu.org/licenses/gpl-3.0.en.html>
#         
        
d <- read.table("SEEDS01/batch.csv", sep=",", 
                col.names=c("id", "light", "airTemp", "airHum", "soilTemp", 
                            "soilHum", "airPress", "remainV"))

json_d <- toJSON(d, pretty=TRUE)

cat(json_d)

write(json_d, "seeds01.json")



