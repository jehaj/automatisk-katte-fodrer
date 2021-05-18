function updateButtons() {
    let deleteButtons = document.getElementsByClassName('delete');
    for (let deleteButton of deleteButtons) {
        deleteButton.addEventListener('click', () => {
            let setting = deleteButton.parentElement.parentElement.parentElement;
            setting.parentNode.removeChild(setting);
        });
    }
}

fetch('http://127.0.0.1:8080/settings')
    .then(response => response.json())
    .then(data => {
        for (const setting of data) {
            console.log(setting);

            let settingsHolder = document.getElementById('settings-holder');
            settingsHolder.insertAdjacentHTML('beforeend', `<div class="box mt-3 mb-0 setting">
                <div class="columns is-vcentered">
                    <div class="column is-narrow">
                        <div class="columns is-vcentered">
                            <div class="column is-narrow p-0 pl-3">
                                <i class="far fa-clock"></i>
                                Tid
                            </div>
                            <div class="column p-0 pl-3">
                                <input style="width: 4.5em;" class="input" type="text"
                                    placeholder="hh:mm" value="${setting.time}">
                            </div>
                        </div>
                    </div>

                    <div class="column is-narrow ml-5">
                        <div class="columns is-vcentered">
                            <div class="column is-narrow p-0">

                                <i class="fas fa-utensils"></i>
                                Mængde foder
                            </div>
                            <div class="column p-0 pl-3">
                                <input style="width: 9em;" class="input" type="text"
                                    placeholder="Et tal fra 1 til 10" value="${setting.value}">

                            </div>
                        </div>

                    </div>
                    <div class="column is-narrow" style="margin-left: auto;">
                        <button class="delete" id="delete-button"></button>
                    </div>
                </div>
            </div>`);
        }
        updateButtons();
    });

addButton = document.getElementById('add-button');
addButton.addEventListener('click', (event) => {
    event.preventDefault();
    let settingsHolder = document.getElementById('settings-holder');
    settingsHolder.insertAdjacentHTML('beforeend', `<div class="box mt-3 mb-0 setting">
    <div class="columns is-vcentered">
        <div class="column is-narrow">
            <div class="columns is-vcentered">
                <div class="column is-narrow p-0 pl-3">
                    <i class="far fa-clock"></i>
                    Tid
                </div>
                <div class="column p-0 pl-3">
                    <input style="width: 4.5em;" class="input" type="text"
                        placeholder="hh:mm">
                </div>
            </div>
        </div>

        <div class="column is-narrow ml-5">
            <div class="columns is-vcentered">
                <div class="column is-narrow p-0">

                    <i class="fas fa-utensils"></i>
                    Mængde foder
                </div>
                <div class="column p-0 pl-3">
                    <input style="width: 9em;" class="input" type="text"
                        placeholder="Et tal fra 1 til 10">

                </div>
            </div>

        </div>
        <div class="column is-narrow" style="margin-left: auto;">
            <button class="delete" id="delete-button"></button>
        </div>
    </div>
</div>`);
    updateButtons();
});

let updateButton = document.getElementById('update-button');
updateButton.addEventListener('click', () => {
    let settingList = document.getElementsByClassName('setting');
    let newSettings = [];
    
    for (let index = 0; index < settingList.length; index++) {
        const settingElement = settingList[index];
        const timevalue = settingElement.children[0].children[0].children[0].children[1].children[0].value;
        const feedvalue = settingElement.children[0].children[1].children[0].children[1].children[0].value
        let mySetting = { time: timevalue, value: feedvalue };
        newSettings.push(mySetting);
    }

    console.log(newSettings);

    fetch('http://127.0.0.1:8080/settings', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(newSettings)
    })
    .then(response => response.json())
    .then(data => console.log(data));
});
