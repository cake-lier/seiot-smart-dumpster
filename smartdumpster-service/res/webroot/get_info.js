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
    $("#available > p").text("yes").css("background-color", "green");
}

function displayUnavailability() {
    $("#available > p").text("no").css("background-color", "red");
}

$(() => {
    $.getJSON("current_data", data => {
        if (data.available === true) {
            displayAvailability();
        } else if (data.available === false) {
            displayUnavailability();
        }
        $("#count > p").text(data.count).css("background-color", "white");
        $("#weight > p").text(data.weight).css("background-color", "white");
    });
    $("#availableButton").click(() => {
        changeDumpsterAvailableState(true);
    });
    $("#unavailableButton").click(() => {
        changeDumpsterAvailableState(false);
    });
    $("#logButton").click(() => {
        $.getJSON("log", data => {
            const headerRow = $("<tr>").append($("<th>", {text: "Date", id: "date"}),
                                               $("<th>", {text: "Number of deposits", id: "count"}),
                                               $("<th>", {text: "Total weight accumulated", id: "weight"}))
            const table = $("<table>").append(headerRow);
            Object.values(data).forEach(day => {
                const row = $("<tr>");
                Object.values(day).forEach((value, index) => {
                    if (index == 0) {
                        row.append($("<th>", {
                            text: value,
                            id: $(headerRow.children()[index]).attr("id")
                        }));
                    } else {
                        row.append($("<td>", {
                            text: value, 
                            id: $(headerRow.children()[index]).attr("id") + $(row.children()[0]).attr("id")
                        }));
                    }
                });
                table.append(row);
            });
            $("body > section:last-child").children("table").remove();
            $("body > section:last-child").prepend(table);
        });
    });
});
