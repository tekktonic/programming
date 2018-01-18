import glob
import re
import string
import hgapi
from mercurial import ui,commands


class repo(object):
    def __init__(self, directory):
        self.name = directory.split("/")[-1]
        self._repo = hgapi.Repo(directory)
        self.author = re.search("user:\s+(.*)\n", self._repo.hg_log(), re.M).groups(0)[0]
        self.msg = re.search("summary:\s+(.*)\n", self._repo.hg_log(), re.M).groups(0)[0]
        self.date = re.search("date:\s+(.*)\n", self._repo.hg_log(), re.M).groups(0)[0]
        self.clone = "http://tekk.in/vcs/" + self.name

    def tablify(self):
        return "<tr><td>" + self.name + "</td><td>" + self.date + "</td><td>" + \
            self.author + "</td><td>" + self.msg + "</td><td>" + self.clone + "</td></tr>"

def generate():
    template = ""
    with open("template.html") as eff:
        template = eff.read()

    repositories = [repo(r).tablify() for r in glob.glob("/home/danny/vcs/*")]
    print(re.sub("\${body}", "<tr><td>Repository</td><td>Last Commit</td><td>Committer</td><td>Commit Message</td><td>Clone URL</td></tr>" + string.join(repositories, ""), template))


generate()
