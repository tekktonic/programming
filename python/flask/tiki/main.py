from flask import Flask, redirect, render_template, request
import textile
app = Flask(__name__)

@app.route("/")
def start():
    return redirect("/Main")

@app.route("/<page>")
@app.route("/<page>/")
def view(page):
    if page[0].islower():
        return redirect("/" + beHelpful(page))
    try:
        f = open('pages/' + page, 'r')
    except IOError:
        return redirect("/" + page + "/edit")

    content = textile.textile(f.read(), html_type='html')
    f.close()
    return render_template("view", title=page, content=content)

@app.route("/<page>/edit", methods=["POST", "GET"])
@app.route("/<page>/edit/", methods=["POST", "GET"])
def edit(page):
    if page[0].islower():
        return redirect("/" + beHelpful(page) + "/edit")
    if request.method == "POST":
        with open("pages/" + page, 'w') as f:
            f.write(request.form["article"])

        try:
            f = open("pages/" + page + ".tags", 'r')
            curset = set(f.read().split("\n"))
            newset = set(request.form['tags'].split(","))

            print("CURSET: " + str(curset) + "\nNEWSET: " + str(newset))
            for x in newset: # add new tags
                if x not in curset:
                    curset.add(x)
                    with open("tags/" + x, 'a') as articles:
                        articles.write(page + "\n")

            for x in curset:
                if x != "":
                    if x not in newset:
                        curset.remove(x)
                        lines = ""
                        with open("tags/" + x, 'r') as articles:
                            lines = articles.readlines()

                            with open("tags/" + x, 'w') as articles:
                                for line in lines:
                                    if line != x + "\n":
                                        articles.write(line)
            f.close()
        except IOError as e:
            print(e)
            with open("pages/" + page + ".tags", 'w') as f:
                for tag in request.form['tags'].split(","):
                    f.write(tag + '\n')
                    with open("tags/" + tag, 'a') as h:
                        h.write(page + "\n")

        return redirect("/" + page)
    else:
        try:
            f = open("pages/" + page, 'r')
            content = f.read()
            f.close()
            f = open("pages/" + page + ".tags", 'r')
            tagin = ""
            for line in f.readlines():
                tagin += (line.strip() + ',')
            tags = tagin[:-1]
            print(tags)
            f.close()
        except IOError:
            print("Hit an IO Error!")
            content = ""
            tags = ""

        return render_template("edit", title=page, content=content, tags=tags)




def beHelpful(name):
    return name[0].upper() + name[1:]


if __name__ == '__main__':
    app.debug = True
    app.run()
