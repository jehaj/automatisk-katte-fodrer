function getWeightFromServer(before) {
    var labels = [];
    var dataForChart = [];

    fetch(`http://127.0.0.1:8080/weight/${before}`, {
    })
        .then(response => response.json())
        .then(data => {
            for (let element of data) {
                let timestamp = element.insertedon;
                timestamp = moment(parseInt(timestamp));
                labels.push(timestamp);

                let value = element.weightvalue;
                dataForChart.push(value);
            }

            myChart.data.labels = labels;
            myChart.data.datasets[0].data = dataForChart;
            myChart.update();
        });
}

var buttonWeek = document.getElementById("button-week");
var buttonMonth = document.getElementById("button-month");
var buttonYear = document.getElementById("button-year");

buttonWeek.addEventListener('click', (event) => {
    getWeightFromServer('week');
});
buttonMonth.addEventListener('click', (event) => {
    getWeightFromServer('month');
});
buttonYear.addEventListener('click', (event) => {
    getWeightFromServer('year');
});

getWeightFromServer('week');

var ctx = document.getElementById('weightChart').getContext('2d');

var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Dit kæledyrs vægt over tid',
            data: []
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            },
            x: {
                type: 'time',
                time: {
                    displayFormats: {
                        hour: 'ddd HH:mm',
                        day: 'ddd DD/MM'
                    },
                    minUnit: 'hour',
                }
            }
        }
    }
});

