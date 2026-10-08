function displayResult(response){
    if(response.id == 1){
        $("#helloResponse").text(response.result);
    }

    if(response.id == 2){
        $("#addResponse").text(response.result)
    }

    if(response.id == 3){
        $("#giphyResponse").attr('src', response.result);
    }
}

function displayError(xhr, statusCode, error){
    let output = `
        ERROR: ${error} <br>
        Message: ${xhr.responseJSON.error.message}
    `;

    $("#error").html(output);
    $("#error").removeClass("hidden");
}

function sendRequest(request){
    $("#error").html("");
    $("#error").addClass("hidden");

    $.ajax({
        url:'https://paul.cs3680.com/labs/api',
        type: 'POST',
        data: JSON.stringify(request),
        contentType: 'application/json; charset=utf-8',
        dataType: 'json',
        success: displayResult,
        error: displayError
    });
};


$("#callHello").click(() => {
    let req = {
        method: "hello",
        params: {
            name: $("#name").val()
        },
        id: "1",
        jsonrpc: "2.0"
    };

    sendRequest(req);
});

$("#callAdd").click(() => {
    let req = {
        method: "add",
        params: {
            value1: $("#value1").val(),
            value2: $("#value2").val()
        },
        id: "2",
        jsonrpc: "2.0"
    };

    sendRequest(req);
});

$("#callGiphy").click(() => {
    let req = {
        method: "giphy",
        params: {
            keyword: $("#keyword").val()
        },
        id: "3",
        jsonrpc: "2.0"
    };

    sendRequest(req);
});
