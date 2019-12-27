function changeDumpsterAvailableState(available) {
    $.ajax({
        url: "state",
        type: "PUT",
        contentType: "application/json",
        data: JSON.stringify({
            "available": available
        }),
        success: () => {
            if (available) {
                displayAvailability();
            } else {
                displayUnavailability();
            }
            alert("Operation was successful");
        },
        fail: () => {
            alert("Operation failed");
        }
    });
}

function displayAvailability() {
    $("#available > p").text("YES").css("color", "#4DC989").parent().css("border-bottom-color", "#4DC989");
}

function displayUnavailability() {
    $("#available > p").text("NO").css("color", "#DC3A61").parent().css("border-bottom-color", "#DC3A61");
}

$(() => {
    $.getJSON("current_data", data => {
        if (data.available === true) {
            displayAvailability();
        } else if (data.available === false) {
            displayUnavailability();
        }
        $("#count > p").text(data.count);
        $("#weight > p").text(data.weight);
    });
    $("#availableButton").click(() => {
        changeDumpsterAvailableState(true);
    });
    $("#unavailableButton").click(() => {
        changeDumpsterAvailableState(false);
    });
    $("#logButton").click(function() {
        $.getJSON("log", data => {
            const headerRow = $("<tr>").append($("<th>", {text: "Date"}),
                                               $("<th>", {text: "Number of deposits", id: "count"}),
                                               $("<th>", {text: "Total weight accumulated", id: "weight"}))
            const table = $("<table>").append(headerRow);
            Object.values(data).forEach(day => {
                const row = $("<tr>");
                Object.values(day).forEach((value, index) => {
                    if (index == 0) {
                        row.append($("<th>", {
                            text: value,
                            id: value.replace(/\//g, "_")
                        }));
                    } else {
                        row.append($("<td>", {
                            text: value, 
                            headers: $(row.children()[0]).attr("id") + " " + $(headerRow.children()[index]).attr("id")
                        }));
                    }
                });
                table.append(row);
            });
            $("body > section:last-of-type").children("table").remove();
            $(this).before(table);
        });
    });
});
