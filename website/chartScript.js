function getWeightFromServer(before) {
    var labels = [];
    var dataForChart = [];

    fetch(`https://lit-lake-24015.herokuapp.com/weight/${before}`, {
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
            label: 'Dit kæledyrs vægt over tid i gram',
            data: []
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true,
                suggestedMax: 6500,
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

