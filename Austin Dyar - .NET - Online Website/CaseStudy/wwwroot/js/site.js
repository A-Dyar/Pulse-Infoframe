// Write your JavaScript code.
$(function () {
    
    // display message if modal still loaded
    if ($('#detailsId').val() !== '') {
        var data = $('#modalbtn' + $('#detailsId').val()).data('details');
        CopyToModal($('#detailsId').val(), data);
        $('#details_popup').modal('show');
    }
    // details click - to load popup on catalogue
    $("a.btn-default ").on("click", (e) => {
        let Id = e.target.dataset.id;
        let data = JSON.parse(e.target.dataset.details); // it's a string need an object
        $("#results").text("");
        CopyToModal(Id, data);
    });
    
});
let CopyToModal = (id, data) => {
        $("#qty").val("0");
        $("#cost").text(data.costPrice);
        $("#desc").text(data.Description);
        $("#detailsGraphic").attr("src", "/images/" + data.GraphicName);
        $("#detailsId").val(id);
};
if ($("#login_popup") !== undefined) {
    $('#login_popup').modal('show');
}
if ($("#register_popup") !== undefined) {
    $('#register_popup').modal('show');
}
$('.nav-tabs a').on('show.bs.tab', function (e) {
    if ($(e.relatedTarget).text() === 'Demographic') { // tab 1
        $('#Firstname').valid();
        $('#Lastname').valid();
        $('#Age').valid();
        $('#CreditcardType').valid();

        if ($('#Firstname').valid() === false || $('#Lastname').valid() === false || $('#Age').valid() === false || $('#CreditcardType').valid() === false ){
            return false; // suppress click
        }
    }
    if ($(e.relatedTarget).text() === 'Address') { // tab 2
        $('#Address1').valid();
        $('#City').valid();
        $('#Region').valid();
        $('#Country').valid();
        $('#Mailcode').valid();

        if ($('#Address1').valid() === false || $('#City').valid() === false || $('#Region').valid() === false || $('#Country').valid() === false || $('#Mailcode').valid() === false) {
            return false; // suppress click
        }
    }
    if ($(e.relatedTarget).text() === 'Account') { // tab 3
        $('#UserName').valid();
        $('#Email').valid();
        $('#Password').valid();
        $('#RepeatPassword').valid();

        if ($('#Email').valid() === false || $('#Password').valid() === false || $('#RepeatPassword').valid() === false || $('#UserName').valid() === false) {
            return false; // suppress click
        }
    }
}); // show bootstrap tab

// for partial view
$(document).on('submit', '#brandForm', function () {
    let $theForm = $(this);
    // manually trigger validation
    $.post('/Brand/SelectItem', $theForm.serialize())
        .done(response => $('#results').text(response))
    return false;
});
$("#jsondatartns").on("click", function (e) {
    busySignal("/Data/Index");
});
let busySignal = (url) => {
    let busyImg = $("<img/>", { src: "/images/wait.gif" });
    $("#busy").empty();
    $("#busy").append(busyImg);
    window.location.href = url;
}