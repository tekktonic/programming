// Eliminate ignored words from our array of words
function deleteUnneeded(strings, list)
{
    var ret = [];
    for (i = 0; i < strings.length; i++)
    {
        // Javascript doesn't have "is this thing in this array?"
        // So we find the index of the thing, and if it's -1 it's not in the array
        if (list.indexOf(strings[i]) == -1)
        {
            ret.push(strings[i]);
        }
    }

    return ret;
}

var verbTable = {
    "kiss": function(object) {output(object + ": *MWAH*!")}
}


function output(text)
{
    var outputArea = document.getElementById("output");
    outputArea.innerHTML += text + "<br/>";
    outputArea.scrollTop = outputArea.scrollHeight;
}

function parse(text)
{
    var ignore = ["to", "from", "and", "or"];
    var verbs = ["lick", "lewd", "kiss"];
    var nouns = ["Danny", "Cade", "Nola", "Doggie"]

    var fixedStrings = deleteUnneeded(text.split(" "), ignore);


    
    // First word should be a verb
    if (verbs.indexOf(fixedStrings[0]) == -1)
    {
        output("invalid verb: " + fixedStrings[0]);
    }
    else
    {
        verb = fixedStrings[0];
    }

    if (nouns.indexOf(fixedStrings[1]) == -1)
    {
        output("invalid noun: " + fixedStrings[1]);
    }
    else
    {
        (verbTable[verb])(fixedStrings[1]);
    }    


}

function handleKeys(form, e)
{
    parse(form.value);
    form.value = "";
}
