function updateButtons() {
    let deleteButtons = document.getElementsByClassName('delete');
    for (let deleteButton of deleteButtons) {
        deleteButton.addEventListener('click', () => {
            let setting = deleteButton.parentElement.parentElement.parentElement;
            setting.parentNode.removeChild(setting);
        });
    }
}

addButton = document.getElementById('add-button');
addButton.addEventListener('click', () => {
    let settingsHolder = document.getElementById('settings-holder');
    settingsHolder.innerHTML += `<div class="box mt-3 mb-0">
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
</div>`;
    updateButtons();
});
