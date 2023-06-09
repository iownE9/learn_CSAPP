url = "https://www.cs.cmu.edu/afs/cs/academic/class/15213-f20/www/code/26-sync-advanced/"
import requests

r = requests.get(url)
if r.status_code != 200:
    raise Exception("r.status_code:", r.status_code)
f = open('url.txt', 'w')

html_doc = r.text

from bs4 import BeautifulSoup

soup = BeautifulSoup(html_doc, "html.parser")

a_nodes = soup.find_all("a")
for link in a_nodes:
    f.write(url + link.get_text() + "\n")
